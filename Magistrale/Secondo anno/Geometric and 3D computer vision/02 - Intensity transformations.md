We will discuss techniques that **modify the intensity of pixels** implemented in the **spatial domain**.

A _spatial domain process_ can be described by:
$$\underbrace{g(x,y)}_{\text{Output image}}=\underbrace{T}_\text{Operator on f over a neighborhood}[\underbrace{f(x,y)}_\text{Input image}]$$
![[Spatial domain.png|376]]

When the neighborhood has size $1\times1$, $g(x,y)$ depends only on the value of $f$ at $(x,y)$ and $T$ is an **intensity transformation function**:
$$s=T(r)$$
where $s$ and $r$ are the _intensity (level of grey)_ of $g$ and $f$ at $(x,y)$.

### Negative
The **negative** of an image with _intensity levels_ in the range $0,...,L-1$ is obtained by:
$$s-L-1-r$$
this processing _enhances white or grey details_ embedded in dark regions.
![[Negative.png|365]]

### Gain and bias
Commonly used operations are multiplication and addition with a constant:
$$s=\alpha r+\beta$$
The two parameters $\alpha>0$ and $\beta$ are often called **gain** and **bias**, they control **contrast** and **brightness** respectively.
![[Gain and bias.png|455]]
### Log transformations
**Log transformations** are useful to _compress the dynamic range_ for images with large variation in pixel values:
$$s=c\log(1+r)$$
where $c$ is an arbitrary constant.

Maps:
- Narrow range of low intensity values in input -> wider range of output levels
- Wide range of high intensity values in input -> to a narrow range of output levels
![[Log transformations.png|273]]![[Log transformed.png|421]]

### Gamma transformations
**Gamma (or power law)** transformations have the following basic form:
$$s=cr^\gamma$$
with $c$ and $\gamma$ positive constants.

Compresses values _similarly to log transformation_, but is _more flexible_ to the parameter $\gamma$.

Curves generated with $\gamma>1$ have the opposite effect of those with $\gamma<1$.


**Gamma correction** is helpful because many _image capture/display devices have power-law response_ (not linear).
>Modern projectors have an intensity-to-voltage response that is a power-law with exponents varying from $1.8$ to $2.5$.

![[Gamma correction.png|645]]
### Contrast enhancement
A whole family of transformations is defined using **piecewise-linear functions**, one of the most useful transformations of this type is one with a _sigmoid shape_:
![[Contrast.png|461]]
![[Contrast enhancement.png|447]]

An extreme case of contrast enhancement is the _step function_, also called **thresholding**:
$$s=\begin{cases}0&r\leq t\\L-1&r>t\end{cases}$$
where $t$ is a constant defined for the whole image, otherwise, if $t$ depends on the spatial coordinates, it is called **adaptive thresholding**.

---
### Image histogram
All the functions seen so far improve the appearance of an image $I$ by varying some parameters, but how can we **find the best values**?

One effective tool is the **image histogram** which allows us to analyze problems in the intensity distribution of an image, practically speaking it is the _empirical distribution of pixels intensities_.

The image histogram is a discrete function:
$$h(r_k)=n_k$$
where $r_k$ is the $k$-th intensity value $(0,...,L-1)$ and $n_k$ is the number of pixels in the image with intensity $r_k$.

Usually it is **normalized** by dividing each component to the total number of pixels, in this way each histogram component is an _estimate of the probability of the occurrence of the intensity $r_k$_.
![[Histogram dark image.png|582]]
![[Histogram light image.png|571]]
### Histogram equalization
Now that we introduced the histogram, we recall the original problem: parameters autotuning, that is: we would like to maximize the intensity range of the image to _catch both the dark and bright details_.

A popular answer to this autotuning problem is finding a mapping function:
$$s=T(r)$$
so that the resulting histogram of $s$ is **flat** (uniform distribution).

The **idea** is that we treat the levels of gray $r$ as [[01 - Random variables#Random variables|random variables]] according to a [[01 - Random variables#PMF, PDF and CDF|PDF]] function.

The **objective** is to transform $f$ in a new gray value $s=T(r)$ in such a way that the output image $s$ uses all the gray levels in a uniform way, we do this by using a [[01 - Random variables#PMF, PDF and CDF|CDF]] multiplied by the maximum value $L-1$.

In the **continuous case**:
$$s=T(r)=(L-1)\int_0^rp_r(w)dw$$
and in the **discrete case** (the real case with digital images):
$$s_k=\frac{L-1}{MN}\sum_{j=0}^kh(r_j)$$
where $h(r_j)$ is the pixel count with value $r_j$ and $MN$ is the maximum number of pixels in the image.
![[Histogram equalization.png|352]]
In this way we are able to get an _almost flat_ histogram by extending the contrast of the image on all the available gamma, note also that, since we are working with discrete values, the final histogram will never be perfectly flat, but it will _still improve the visual constrast_.

### Histogram matching
Sometimes when don't want a fully flat histogram, instead we want to **specify a shape**, for this reason we will use histogram equalization for **histogram matching**.

Supposing that we have an input image with intensities described by $r$ with PDF $P_r(r)$ and a specified target PDF described by $z$ with a given PDF $p_z(z)$, we define a new function $G(z)$ as:
$$G(z)=(L-1)\int_0^zp_z(t)dt$$
- $G(z)=s=T(r)$ are RV with the same uniform distribution (i.i.d.)
- $G$ is monotonically increasing because is a CDF, so it can be inverted

Therefore, we can write:
$$z=G^{-1}(s)=G^{-1}(T(r))$$

The **algorithm** is:
1. Compute the PDF (normalized histogram) of the input image $p_r(r)$
2. Use the specified PDF $p_z(z)$ to compute $G(z)$
3. Invert $G(z)$
4. Equalize the input image to obtain $s$, then apply $G^{-1}(s)$ to the equalized image $s$ to obtain the output image
![[Histogram matching.png|559]]
In the **discrete** case, the function $G(z)$ is implemented as a lookup table with $L$ entries.

#### Histogram for thresholding
Returning to the thresholding problem, when doing global thresholding, a common problem is to automatically find a good threshold $t$ that separates well dark from bright areas.

If an image is **separable through thresholding**, we expect a _range of mid-tones intensities with low probability_.
Thresholding is essentially a **clustering problem** in which two clusters (black and white) are sought.

**Otsu thresholding**
The idea is to find the optimum threshold $T$ so that the variance of each class _within-class variance_ is minimized.
$$\arg\min_TP_1\sigma^2_{c_1}+P_2\sigma^2_{c_2}$$
![[Histogram for thresholding.png|318]]

- $P_1(T)$: probability that a pixel is assigned to $C_1$ given a threshold $T$
- $P_2(T)$: probability that a pixel is assigned to $C_2$ given a threshold $T$

Operatively, we can try all the possible values of $T$ from $0$ to $L-1$ and keep the threshold for which the above function is minimized.

Otsu demonstrated that the optimal $T$ that minimizes the within-class-variance also _maximizes_ the between-class-variance.

**Otsu algorithm**:
1. Compute the normalized histogram of the input image, denote each component of the histogram as $p_i,i=0,1,...,L-1$
2. Compute the cumulative sums $P_1(T)$ for all $T=0,...,L-1$
3. Compute the cumulative means $m(T)$ for all $T=0,...,L-1$
4. Compute the global intensity mean $m_G$
5. Compute the between class variance $\sigma_B^2(T)$ for all $T=0,...,L-1$
6. Apply threshold with a value of $T$ for which $\sigma_B^2$ is maximum

>[!Attention]
>Otsu thresholding iterates on image histogram and not on image pixels as other global methods (e.g. [[03 - Clustering#K-means|K-means]]).