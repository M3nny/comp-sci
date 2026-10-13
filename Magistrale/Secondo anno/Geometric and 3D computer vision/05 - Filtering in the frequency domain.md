In this chapter we're going to see how the **Fourier transform** and the frequency domain can be used for **image filtering**.

#### Complex numbers
A complex number $C$ is defined as:
$$C=R+jI$$
where $R$ and $I$ are real numbers, and $j$ is an imaginary number so that $j^2=-1$.
$R$ is the _real part_ and $I$ is the _imaginary part_.

A complex number can be represented in polar coordinates:
$$\underbrace{r=\sqrt{R^2+I^2}}_\text{Modulus}\quad\underbrace{\theta=\arctan\frac{I}{R}}_\text{Phase}$$
The **Euler formula** is given as:
$$e^{j\theta}=\cos\theta+j\sin\theta$$
from which:
$$C=\sqrt{C\overline C}e^{j\theta}$$

### Discrete Fourier transform
Let $f$ be a function composed by a finite number of $M$ discrete samples:
$$f(x):[0,...,M-1]\to\mathbb C$$
Then, there exists a set of $M$ complex coefficients:
$$F(0), F(1),..., F(M-1)\in\mathbb C$$
such that:
$$f(x)=\frac{1}{M}\sum_{u=0}^{M-1}f(u)e^{j2\pi xu/M}$$
In other words: any discrete finite function can be expressed as the sum of sines and cosines (or complex exponentials), of different frequencies, each multiplied by a different coefficient $F(0), ..., F(M-1)$.
$$\begin{align}
f(x)&=\frac{1}{M}\sum_{u=0}^{M-1}f(u)e^{j2\pi xu/M}\\
&=\frac{1}{M}\sum_{u=0}^{M-1}F(u)\left(\cos\left(\frac{2\pi u}{M}x\right)+j\sin\left(\frac{2\pi u}{M}x\right)\right)
\end{align}$$
![[Fourier transform.png|471]]
The coefficients $F(0),..., F(M-1)\in\mathbb C$ can be computed with the so-called **discrete Fourier transform**:
$$\begin{align}
F(u)&=\sum_{x=0}^{M-1}f(x)e^{-j2\pi xu/M}\\
&=\frac{1}{M}\sum_{x=0}^{M-1}F(x)\left(\cos\left(\frac{2\pi xu}{M}\right)-j\sin\left(-\frac{2\pi xu}{M}\right)\right)
\end{align}$$
Fourier transform is essentially a **change of basis** from the **spatial domain** to the **frequency domain**.

Since $F(u)$ is a complex function, it can be expressed in polar form:
$$F(u)=|F(u)|e^{j\theta(u)}$$
- $|F(u)|=\sqrt{R^2(u)+I^2(u)}$ is called the **power spectrum**
- $\theta(u)=\arctan\frac{Imag(F(u))}{Real(F(u))}$ is the **phase angle**

#### 2D DFT
DFT can be computed for any-dimensional input function, in particular the 2D DFT is useful when working with images.

**2D DFT**
$$ F(u, v) = \sum_{x=0}^{M-1} \sum_{y=0}^{N-1} f(x, y) e^{-j 2\pi \left( \frac{ux}{M} + \frac{vy}{N} \right)} $$
This transforms an image $f(x,y)$ of size $M\times N$ into its frequency representation $F(u,v)$.

**Discrete inverse Fourier transform**
$$ f(x, y) = \frac{1}{MN} \sum_{u=0}^{M-1} \sum_{v=0}^{N-1} F(u, v) e^{j 2\pi \left( \frac{ux}{M} + \frac{vy}{N} \right)} $$
This reconstructs the spatial image from its frequency coefficients.

The transform breaks an image down into a weighted sum of 2D complex exponential wave patterns called **basis images**, varying at different frequencies and orientations.

**Spectrum Centering (shifting)**: by default, the origin of the DFT is at the top-left corner, but to analyze frequencies easily, we shift the zero-frequency component to the center of the spectrum at $(M/2, N/2)$.
![[2D DFT top-left origin.png|505]]
![[2D DFT centered origin.png|510]]
#### 2D DFT spectrum
**Translating** an image $f(x,y)$ in the spatial domain does not change its power spectrum, it only affects the phase angle.

**Rotating** an image by an angle $\theta$ rotates its Fourier transform by the same angle (and vice-versa), rotating an image by $180^\circ$ yields its complex conjugate.

- **Power spectrum (modulus)**: determines the amplitudes or intensities of the sinusoidal components that combine to form the image
- **Phase angle**: contains most of the structural information, defining _where_ discernible objects and edges are located in the image space

**Reconstructing an image** using only the phase angle preserves object boundaries remarkably well.
![[Image reconstruction using phase angle only.png|531]]
![[Image reconstruction using spectrum only.png|529]]
#### Convolution theorem
The fundamental tool enabling frequency-domain filtering is the **convolution theorem**, which states that the _convolution in the spatial domain_ is **equivalent** to _multiplication in the frequency domain_, and vice-versa:
$$f(x,y) * h(x,y) \iff F(u,v)H(u,v)$$
$$f(x,y)h(x,y) \iff F(u,v) * H(u,v)$$

**The filtering pipeline**: frequency domain filtering involves taking the DFT of an input image, multiplying it by a filter transfer function $H(u,v)$, and computing the inverse DFT to get the processed result:
$$g(x,y) = \underbrace{\mathfrak{S}^{-1}}_\text{IFT}[\underbrace{H(u,v)}_\text{Filter function}\underbrace{F(u,v)}_\text{DFT of the input image}]$$

### Low-pass filters
Low frequencies correspond to slowly varying intensity components (smooth background areas), while high frequencies correspond to sharp intensity transitions like edges and noise.
![[Low-pass filter.png|468]]
**Low-pass filters** attenuate high frequencies, causing _blurring_.

**Ideal Low-Pass Filter (ILPF)**
Cuts off all frequencies sharply outside a circle of radius $t$ (cutoff frequency):
$$H(u,v) = \begin{cases} 1, & \sqrt{u^2 + v^2} \le t \\ 0, & \sqrt{u^2 + v^2} > t \end{cases}$$
![[ILPF.png|339]]
Sharp cutoffs cause unwanted _ringing artifacts_ in the spatial domain.

**Butterworth Low-Pass Filter (BLPF)**
Smoothly transitions between passed and filtered frequencies depending on order $n$ and cutoff distance $D_0$:
$$H(u,v) = \frac{1}{1 + \left(\frac{\sqrt{u^2 + v^2}}{D_0}\right)^{2n}}$$
![[BLPF high cutoff.png|372]]
![[BLPF low cutoff.png|373]]
![[BLPF order effect.png|497]]

_Lower orders_ (e.g. $n=1, 2$) provide less smoothing but minimal ringing, _higher orders_ approach the sharp behavior (and ringing) of ideal filters.

**Gaussian Low-Pass Filter (GLPF)**
Smooth and continuous everywhere with no sharp edges:
$$H(u,v) = e^{-\frac{u^2 + v^2}{2D_0^2}}$$
Provides smooth blurring _without any ringing artifacts_.

### High-pass filters
High-pass filters attenuate low frequencies and pass high frequencies, **enhancing edges** and fine details at the expense of overall contrast.![[High-pass filter.png|489]]
**Ideal High-Pass Filter (IHPF)**
The exact opposite of the ILPF, filtering out frequencies within a radius $t$:
$$H(u,v) = \begin{cases} 0, & \sqrt{u^2 + v^2} \le t \\ 1, & \sqrt{u^2 + v^2} > t \end{cases}$$
![[IHPF high cutoff.png|334]]

**Butterworth High-Pass Filter (BHPF)**
Smooth transition alternative to the ideal high-pass filter.
![[BHPF high cutoff.png|342]]

**Laplacian in the Frequency Domain**
The Laplacian operator can be efficiently implemented in the frequency domain using the filter:
$$H(u,v) = -4\pi^2(u^2 + v^2)$$$$\nabla^2 f(x,y) = \mathfrak{S}^{-1}\{H(u,v)F(u,v)\}$$

### Notch filters
Notch filters are band-stop filters that **reject specific localized frequency** components in a defined neighborhood.

To ensure the output image remains real (not complex), notch filters **must be conjugate symmetric** about the origin (if a notch exists at $(u_0, v_0)$, a matching notch must exist at $(-u_0, -v_0))$.

They are frequently used to remove periodic noise patterns from images, such as **Moiré patterns** found in scanned newspapers or fabrics, which appear as bright symmetric impulse bursts in the Fourier spectrum.
![[Notch filter input.png|328]]![[Notch filter output.png|345]]![[Notch filter result.png|359]]
### Image restoration
When an image is degraded by a linear, position-invariant degradation function $h(x,y)$ and additive noise $\eta(x,y)$, the model is:
$$g(x,y) = h(x,y) * f(x,y) + \eta(x,y) \implies G(u,v) = H(u,v)F(u,v) + N(u,v)$$

**Direct Inverse Filtering**
Attempts to recover the original image by simple division:
$$F(u,v) = \frac{G(u,v)}{H(u,v)} - \frac{N(u,v)}{H(u,v)}$$
Highly unstable when $H(u,v)$ is close to zero, and it drastically amplifies small noise terms $N(u,v)$.

**Wiener Filtering**
A statistically optimal approach (in a least-squares sense) that balances signal restoration and noise suppression using the power spectra of the noise ($S_n$) and signal ($S_f$):
$$\hat{F}(u,v) = \left[ \frac{\overline{H(u,v)}}{\vert{}H(u,v)\vert{}^2 + \frac{S_n(u,v)}{S_f(u,v)}} \right] G(u,v)$$
In practice, the power spectra ratio is often approximated or tuned manually as a constant noise-to-signal ratio.
