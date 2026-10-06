A **spatial filter** is an _operation_ performed on a neighborhood of image pixels, its result is a new pixel with coordinates equal to the centre of the neighborhood and whose value is the result of the filtering operation.

The filter is _swept throughout all the input image space_.

### Linear filters
If the operation performed is linear, the filter is called linear spatial filter, and is defined by a **coefficient matrix $W$**.

The operation performed is the sum of products of the filter coefficients and the image pixels encompassed by the filter.
$$g(x,y)=\sum_{s=-a}^a\sum_{t=-b}^bw(s,t)f(x+s,y+t)$$
Linear spatial filtering can be described in terms of _correlation_ and _convolution_.

**Correlation**
The process of moving a filter mask over the image and computing the sum of products at each location.

>[!Example] Correlation
>$$f(x) = 0 0 0 1 0 0 0 0$$
>$$w(x) = 1 2 3 2 8$$
>
>When moving the mask across the image there will be a part that does not overlap, for this reason we have to add _padding_.
>
>$$f(x)=0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0$$
>
>The result after 11 shifts is:
>$$0 0 0 8 2 3 2 1 0 0 0 0$$
>
>After that we remove the padding so that the result has the same size as the input:
>$$0 8 2 3 2 1 0 0$$
>
>- The first value of correlation corresponds to zero displacement, the second corresponds to one unit displacement, and so on
>- Correlating a filter $w$ with a function that contains all 0s and a single 1 yields a result that is a copy of $w$, but rotated by 180°

**Convolution**
Like correlation, but the filter mask is first rotated by 180° before the shift operations.

In case of 2D functions, like images, the correlation works in a similar manner, for a filter $M\times N$, we first pad the image with a minimum of:
- $M-1$ rows at the topo and bottom
- $N-1$ columns at the left and right
![[2D convolution.png|357]]

### Smoothing spatial filters
Smoothing filters are typically used for **blurring/noise reduction**.
The output (response) of a smoothing, filter is simply the average of the pixels contained in the neighbourhood of the filter mask.
![[Smoothing spatial filter.png|380]]
### Gaussian filter
A special type of weighted average filter is the **Gaussian filter**, where each element has the form:
$$e^{-\frac{1}{2}\frac{x^2+y^2}{\sigma^2}}$$
Gaussian filter gives a better "less blocky" result, but is computationally more expensive since it involves floating-point operations.
![[Gaussian filter.png|521]]
### Order-statistic filters
Order-statistic filters are **non-linear** spatial filters whose response is based on:
1. Ordering the pixels in the neighborhood
2. Replacing the value of the central pixel with the value determined by the ranking result

**Median filter**
Replaces the value of a pixel by the _median of the intensity values_ in the neighborhood of that pixel.

**Max-filter**
Replaces the value of a pixel with the _brightest_ intensity value in the neighborhood.

**Min-filter**
Replaces the value of a pixel with the _darkest_ intensity value in the neighborhood.

### Filter and noise
Smoothing and median filters are particularly useful for **image denoising**.

**Additive noise**
$$\hat I(x,y)=I(x,y)+\omega\quad\omega\sim N(0,\sigma^2)$$
**Salt & pepper (impulse) noise**
$$\hat I(x,y)=\begin{cases}I(x,y)&\text{if }q=0\\L-1&\text{if }q=1\\0&\text{if }q=2\end{cases}$$
![[Denoising.png|564]]
### Sharpening filters
The principal objective of sharpening is to _highlight transitions in intensity_.

One simple approach is **unsharp masking**:
1. Blur the original image
2. Subtract the blurred image from the original to obtain a mask
3. Add the mask to the original (multiplied by a constant)


|               | Averaging pixels in a neighborhood |   Differences between pixels in a neighborhood   |
| :-----------: | :--------------------------------: | :----------------------------------------------: |
| **Operation** |            Integration             |                 Differentiation                  |
|  **Effect**   |              Blurring              |                    Sharpening                    |
| **Useful to** | Reduce noise (but we lose details) | Enhance details (but we also increase the noise) |

### Derivatives in images
Derivatives of digital discrete functions are defined in term of differences.

**First-order** derivative of a one-dimensional function:
$$\frac{df}{dx} = \lim_{\epsilon \to 0} \frac{f(x + \epsilon) - f(x)}{\epsilon} \approx f(x + 1) - f(x)$$
**Second order** derivative:
$$\frac{d^2 f}{d^2 x} \approx f(x + 1) + f(x - 1) - 2f(x)$$
![[Derivatives in images.png|434]]
- Zero in constant-intensity areas
- Non-zero on an onset and end of ramps and steps
- Zero along ramps

For **sharpening** we want to highlight intensity transitions (_edges_):
- _First-order derivative_: produces thick edges because the derivative is nonzero along a ramp
- _Second-order derivative_: produces a "double edge" one pixel thick, separated by zeros

### Laplacian filtering
The Laplacian is the simplest isotropic second-order derivative operator:
$$\nabla^2f=\frac{\partial^2f}{\partial x^2}+\frac{\partial^2f}{\partial y^2}$$
In its **discrete form**, the Laplacian can be expressed in terms of finite differences:
$$\nabla^2 f(x, y) = f(x + 1, y) + f(x - 1, y) + f(x, y + 1) + f(x, y - 1) - 4f(x, y)$$

Since derivatives are linear operators, _the Laplacian is a linear operator_ and hence can be implemented as a convolution with a proper filter mask.

The Laplacian operator _highlights intensity discontinuities_ in an image and <u>deemphasizes regions with slowly varying intensity levels</u>.

If we subtract the effect of the Laplacian operator to the original image, we will **sharpen** the edges while preserving background slowly-varying gradients.
$$g(x, y) = f(x, y) - c(\nabla^2 f(x, y))$$
![[Laplacian filtering.png|554]]
