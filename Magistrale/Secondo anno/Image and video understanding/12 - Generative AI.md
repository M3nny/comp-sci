We can think of a **manifold** as the higher dimensional generalization of "a sheet of paper is a 2D surface sitting inside 3D space".

When applying this concept to images, if we consider the space of all possible $100\times100$ images, _almost every point in that space is random noise_, whilst meaningful photos only occupy a thin structured part of it (a manifold), and images of a particular class (faces, cats, ...) sit on even smaller sub-manifolds within that.

![[Cat manifold.png|300]]

The following methods are all, in different ways, methods for **learning a manifold** so we can move around it (compress data, generate new samples, or denoise back into it).

### Autoencoders
An autoencoder is an **unsupervised network** with two halves:
- **Encoder**: compresses the input into a lower-dimensional latent code
- **Decoder**: reconstructs the original input from that code
![[Autoencoder.png|400]]
This is **trained** by minimizing reconstruction loss (input vs output), no labels needed.

A dimensionality reducing transformation generally **can't be perfectly invertible everywhere**, but an autoencoder tries to learn one that's invertible specifically for points on the data manifold.

From a practical point of view, if we feed an autoencoder with noisy (off-manifold) data, it will _tend to snap the output back toward clean, on-manifold data_ (i.e. autoencoders naturally denoise).

The encoder can be used to **initialize a supervised model** after throwing away the decoder, now we can attach a classification head and fine-tune the encoder jointly with the classification head on some other task.

We could use an autoencoder for **image coloration**, specifically it would be a **conditional autoencoder** since it receives in input a 1 channel image and it is expected to output the same image but with 3 channels.

**Designing the loss function** is important, and using a plain pixel-wise L2 loss produces blurry outputs because it averages over all plausible reconstructions.![[Autoencoder L2.png|449]]We'll learn a loss function by training a network to discriminate between images that are on the manifold and images that aren't.

### Variational autoencoders
The **problem with plain autoencoders** is that the latent space they learn is not continuous.
It's great at reconstructing training points, but the space between those points **can contain holes**, so when we decode a random or interpolated latent point (generate a new image) _we often get garbage_, because nothing forced the space to be smooth (we don't know what distribution those latent points follow).

**Generating an image** can be reframed as: take a sample from something simple (e.g. uniform distribution) and pass it through some complicated function $f$, which in our case can be a neural network, that network will be for us, the _decoder_.

We rephrase it by saying that we want a function $f$ such that:
$$x=f(z)$$
produces a realistic image.

The function $f$ is _highly complex_, so we let a neural network learn it from data, that network, again, is the decoder.
>$z$ is the low dimensional **latent code** produced by the encoder and used by the decoder to generate an image.

The **Variational AutoEncoder (VAE)** fix is: instead of the encoder mapping an input to one fixed point ($z$) in latent space, it computes two vectors:
- **Mean** $\mu(x)$
- **Standard deviation** $\sigma(x)$
>These are parameters of a small Gaussian distribution.

For each latent dimension, the _encoder computes a "center" and a "spread"_, which together define a little bell curve.
![[VAE bell.png|445]]

To **compute $z$** we extract a value from the Gaussian distribution of each latent dimension and then stack them to form a vector $z$.
![[VAE bell extract.png|328]]
Just letting the encoder output a distribution instead of a point _wouldn't be enough_ by itself, the model could still learn wildly different, disorganized distributions for different inputs, leading to the same "hole" problem.

The fix has a second half: **the training loss also penalizes each input's distribution** $q(z|x)$ for straying too far from a fixed, simple reference distribution $p(z)=\mathcal N(0,I)$.

That penalty is what _forces every input's little Gaussian to stay roughly Gaussian-shaped_, roughly centered near the origin, and roughly the same "size" as all the others

In this way we get a latent space that's _smoothly packed and continuous_, that's why after training, we can throw the encoder away and just **sample $z$ directly** from $\mathcal N(0,I)$.

>[!Tip] Variational inference
>This whole setup is doing **variational inference**:
>- $p(z)$ _prior_: is out assumption about how latent codes are distributed across the whole dataset, before seeing any specific image, this is chosen to be a simple distribution
>- $q(z|x)$ _approximate posterior_: what the encoder computes, ideally we'd want the true posterior $p(z|x)$ (the real distribution of latent codes that could have produced the image), but computing that exactly is not feasible, so we approximate it with a simple Gaussian function, and the encoder's job is to output the best-fitting $\mu$, $\sigma$ for that approximation
>- $p(x|z)$ _the likelihood_: what the decoder computes (given a latent code, what image does it correspond to)


**Training** maximizes the **ELBO** (evidence lower bound), which balances two competing pressures:
- **Reconstruction accuracy**: $p(x|z)$ should actually produce something close to the real $x$ (this pushes the decoder to be a good decoder, and the encoder to encode useful information)
- **KL-divergence to the prior**: $q(z|x)$ should stay close to $p(z)=\mathcal N(0,I)$ (this is the regularizer)

These two pressures _pull in slightly opposite directions_.
>Pure reconstruction accuracy alone would want each input's distribution to shrink to a tiny, precise point (like a plain autoencoder), while the KL term prevents that by demanding some spread and centering.

![[VAE training.png|540]]
Training needs gradients to flow from the **reconstruction loss** all the way back through the sampling step to the encoder's weights, so the encoder learns to produce better $\mu,\sigma$, but randomly drawing $z$ is a stochastic operation, which **has no derivative**.

The **reparametrization trick** fixes this by rewriting the sample as:
$$z=\mu(x)+\sigma(x)\odot\epsilon\quad\epsilon\sim\mathcal N(0,I)$$
Now the randomness $\epsilon$ is pulled out as an external input with no trainable parameters attached to it at all, it's just noise sampled fresh each time.

### Generative adversarial networks
A **Generative Adversarial Network (GAN)** is composed by two networks trained against each other:
- **Generator ($G$)**: similar to a decoder, it maps points from a latent space into images
- **Discriminator ($D$)**: classifier whose job is to look at an image and decide if it is real (from the training set) or fake (produced by $G$)

**Training is adversarial**, the two networks have _opposing goals_ and are updated together, each trying to beat the other.
![[GAN discriminator.png|473]]

We recall that plain _pixel-wise loss (L2) produces blurry results_ because it averages over all plausible outputs.

GANs, instead of hand-designing a better loss function, they **learn a loss function**, in fact, from $G$'s perspective, $D$ is a loss function.
Since $D$ scores how realistic an image looks, that realism score is what $G$ is trained to maximize, then the loss function is a trained neural network formularized as a **minimax game**:
$$\arg\min_G\max_D\mathbb E_{x,y}[\underbrace{\log D(G(x))}_\text{Identify generated images as fake}+\underbrace{\log(1-D(y))}_\text{Identify training images as real}]$$

Similarly to the previous _conditional autoencoders_ we have **conditional GANs** which are able to generate high-resolution images conditioned on low-resolution input.

### Diffusion models
We recall that real images occupy a thin manifold inside a larger space of possible pixel arrangements, **diffusion models** are a method for walking from that surrounding noise onto the manifold, _one step at a time_.

We can't train a "denoise a little bit" network without examples of noisy images paired with slightly less noisy version, for this reason we **manufacture noisy images** by progressively adding Gaussian noise to them, this is called the **forward process**.
>This is just a simple method for progressively destroy an image.

>[!Example] Forward process
So in practice, we take a real image $x_0$, add a small amount of noise and produce $x_1$, then add a little more to produce $x_2$, up until $x_T$ is indistinguishable from pure random noise.

The network job, at every step is: given a noisy image $x_t$, predict how to get to a slightly cleaner $x_{t-1}$, this is usually framed as **predicting the noise that was added**, instead of directly the clean image, but the effect is the same, that is: learning a function that points back toward the manifold.
>This is much easier than generating a perfect image from scratch.

**Generating an image** consists in walking from random noise $x_T$ up to $x_0$ which is a coherent image that has never been seen during training, built from learned steps away from randomness.
![[Diffusion back to cat manifold.png|451]]

Diffusion models are **slower than GANs** since they have to make steps in order to generate and image, but they're **easier to train** since it is a single network trained on one task, rather than maintaining a balance between adversarial networks.

Diffusion models can be mixed with image that are partially real images and partially noise (the thing to generate), for example inpainting is a good use case:
![[Diffusion inpainting.png|562]]

The major problem is that with the base version, _generating cats requires one fully-trained diffusion model_, and generating llamas requires an entirely separate one, this doesn't scale well, for this reason there are two main ideas to fix this.

**Text label as conditioning**
Alongside a noisy image, we feed in a _label_ (e.g. llama) directly into the diffusion network.

The network _sees both the noisy input and the label at every denoising step_, and learns to produce output consistent with that label.
>One network, many possible labels, instead of one network per concept.

![[Diffusion text label as conditioning.png|463]]

**Condition using a LLM**
Instead of feeding in a raw label, we first pass a prompt to a LLM, which outputs a _language representation_ that includes relationships between verbs and subjects, then this representation is what conditions the diffusion network, not the raw text.

This gives us _composability_: the diffusion model can generate combinations of concepts it never saw paired together during training, because LLM's representation captures the relationship between concepts.
![[Diffusion condition using a LLM.png|327]]
