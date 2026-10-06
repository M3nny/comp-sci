We'll now discuss how a real-world scene is imaged through a digital camera.

To be able to see any 3D scene, our eyes or digital camera need to capture the **light radiation** reflected from scene surfaces.

### Visible light
Light has a **dual nature**:
- Can behave like a _particle (photon)_: travels in a straight line
- Can behave like a _wave_: refraction, diffraction

Visible light is part of **electromagnetic spectrum**, which can be expressed in terms of _wavelength_ $\lambda$ or _frequency_ $v$.
![[Radiance and luminance.png|547]]
**Brightness** (unlike _radiance_ and _luminance_, see the image above), is a subjective descriptor of light "intensity" and is one of the key factors in describing color sensation.

### BRDF
When light hits a surface, it is scattered and reflected, the most general way to model this interaction is through a 5-dimensional function called **BRDF (Bidirectional Reflectance Distribution Function)**, which can be obtained through _physical modelling_.
>In practice, most of the times, we don't account for the full BRDF, but only a simple combination of _diffuse and specular reflection_ models.

**Diffuse reflection** scatters light uniformly in all directions, while **specular reflection** depends strongly on the direction of the outgoing light 
![[Phong model.png|606]]
### Digital image sensors
An imaging sensor **transforms incoming light radiation** reflected from a 3D scene into voltage, and usually sensors are arranged in linear or 2D arrays.
![[CCD vs CMOS.png|383]]
A/D conversion from voltage to a digital signal can happen in two ways:
- _CCD_: at the end of each row/column
- _CMOS_: directly at each sensing cell

### Image as a function
Mathematically, we model an image as a function:
$$I:\Omega\subset\mathbb R^2\to\mathbb R$$
The **domain** is a (usually rectangular) subset of the real image plane.
$I(x,y)$ is proportional to the amount of light energy that is collected at the image plane coordinates $(x,y)$, this amount of energy is called **intensity**.

A **continuous real image is converted** into a digital one through a process of _sampling_ and _quantization_.

**Sampling**
Reduces the image domain to a finite (discrete) set of spatial coordinates.
$$\mathbb R^2\to M\times N$$
We usually consider an equispaced grid of values in an area (matrix), this reflects the regular arrangement of cells in a CMOS or CCD sensor, each sample is called a **pixel**.

**Quantization**
Reduces the sensor response (function codomain) to a finite set of values.
$$\mathbb R\to[0,...,2^b]$$
The intensity (output) of the function must also be discretized (quantized) in a finite set of values to be digitized and used in a computer.
>Image codomain is divided into a set of values and each $I(x,y)$ is rounded to the closest one.

![[Quantization.png]]

### Image resolution
The digitalization process depends by matrix size $M,N$ and the number of quantized intensity levels $L$.

$M,N$ are related to the _spatial resolution_ of an image, $L$ is related to the _intensity resolution_.

**Image resolution**
Typically referred to as the _number of pixels_ that compose the image.

**Spatial resolution**
Defined as the number of pixels (dots) per unit distance (inches), which is measured in _DPI_.

**Intensity resolution**
Refers to the smallest discernible change in intensity level, which is usually a power of 2.
![[Intensity resolution.png|570]]
### Dynamic range/contrast
We define the **dynamic range** of an **imaging system** as the ratio:
$$\text{Dynamic range}=\frac{\max(\text{measurable intensity})}{\min(\text{detectable intensity level})}$$
Similarly we can define **contrast** in an image as:
$$\text{Contrast}=\max(\text{intensity})-\min(\text{intensity})$$

### Relationships between pixels
A pixel $p$ at coordinates $(x,y)$ has 2 horizontal and 2 vertical neighbors called **4-neighbors of $p$**.
$$N_4(p)=\{(x+1,y), (x-1,y), (x,y+1), (x,y-1)\}$$
![[N4p.png|230]]
A pixel also has 4 **diagonal neighbors**:
$$N_D(p)=\{(x+1,y+1), (x-1,y-1), (x-1,y+1), (x+1,y-1)\}$$
![[NDp.png|223]]
All the neighbors of $p$ are called **8-neighbors**:
$$N_8(p)=N_4(p)\cup N_D(p)$$
![[N8p.png|226]]
A path from a pixel $p=(x,y)$ to $q=(s,t)$ is a sequence of pixels with coordinates:
$$(x_0,y_0),...,(x_n,y_n)$$
Where:
$$(x_0,y_0)=(x,y)\quad(x_n,y_n)=(s,t)$$
For each pixel, $(x_i,y_i)$ and $(x_{i-1},y_{i-1})$ are adjacent, that is: $(x_i,y_i)\in N_{4,D,8}(x_{i-1},y_{i-1})$.

Two pixels $p$ and $q$ are **connected** if there exists a path between them, furthermore, the set of all pixels connected to $p$ is called **connected component**.

Let $R$ be a subset of pixels in an image, $R$ is called a **region** if it contains only one connected component.