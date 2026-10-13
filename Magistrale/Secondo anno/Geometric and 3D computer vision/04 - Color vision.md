The colors that humans and animals perceive in an object are determined by the light **wavelength reflected by the object**.

To **distinguish a color** from another we use:
- _Brightness_: achromatic notion of intensity
- _Hue_: dominant wavelength in a mixture of light waves
- _Saturation_: amount of white light mixed with a hue

### Human vision
In the human cornea  there are three types of cones (receptors), and there are 2%, 33% and 65% receptors sensitive to blue, green and red light respectively.
**Our perception of colors** is the result of the simultaneous stimulus of the three different classes of cones.
![[Sensitivity regions for humans.png|369]]

### Color matching
Given three suitable **primary colors**: red, green and blue (as defined in the 1930 by the CIE), we want to map a combination of such three primaries to _any visible wavelength_.

To do so we use **color matching**: by adding some red to the test light, we can match it using only green and blue.
Since the sensitivity regions of the three classes of cones **overlap**, matching certain cyan test lights requires subtracting red light, resulting in _negative values_ in the color matching functions.

For this reason [CIE](https://en.wikipedia.org/wiki/International_Commission_on_Illumination) created the **XYZ color space** using three virtual primaries $(X,Y,Z)$ to eliminate the need for negative values, yielding a larger color space than RGB.

The **chromaticity diagram** is retrieved by normalizing $XYZ$ coordinates:
$$x=\frac{X}{X+Y+Z}\quad y=\frac{Y}{X+Y+Z}$$
brightness is discarded, allowing 2D representation of chromaticity.
![[Chromaticity diagram.png]]

- Boundary points represent pure monochromatic colors
- Straight lines between points define additive color mixtures

We define **color Gamut** the subset of colors that can be successfully reproduced by a fixed set of three primary colors (triangles cannot enclose the entire diagram).

### Color mixing
We define **additive primaries** red, green and blue and combine them to form secondary colors and produce white when mixed fully (used in displays like LCD screens).

When talking about pigments, we reason about **subtractive primaries**, in this model we use cyan, magenta and yellow as primaries which absorb specific light wavelengths and reflect others, combining all three yields black.
![[Mixing colors.png|624]]
#### Color models
A **color model** is a specification of:
- A coordinate system
- A subspace within that system where each color is represented by a single point

**RGB** is a 3D space in which  the 3 components are the amount of red, green and blue, and it works on _additive mixing_, and therefore we have black at the origin and white at the opposite corner of the cube.
![[RGB.png|525]]
**CMY** space is similar to RGB but is used in _subtractive synthesis_, this time we have white at the origin (there is no pigment) and black at the opposite corner of the cube.
Mixing all of its primaries gives a muddy-looking black, for this reason we add a fourth color, that is: _black_, giving life to **CMYK**.
![[CMYK.png|219]]

In the **HSI (Hue, Saturation, Intensity)** color space, we explicitly map those 3 color characteristics:
- _H_ is an angle going from $0$ to $2\pi$
- _S_ is the saturation
- _I_ ranges from $0$ (black) to $1$ (white)

![[HSI.png|293]]
**YUV** is similar to HSI, but the color vector is parametrized by $u,v$ components instead of Hue (angle) and Saturation (S), in practice we have a polar (HSI) vs cartesian (YUV) representation.

### Digital color image processing
Digital sensors use a **Color Filter Array (CFA)**, predominantly the **Bayer pattern**, which features _twice as many green filters_ as red and blue because human luminance perception is driven mostly by green.

The process of interpolating missing color values so that we have valid RGB values for all the pixels is known as **demosaicing**.

When working with color images, we can operate on each channel individually and perform _intensity transformations_ (we have to choose the most adequate color space).

Operations can be applied channel-wise, adjusting RGB components _equally alters brightness without drastically shifting hues_, while selective channel manipulation fixes color imbalances.

We can do **histogram equalization on colors**, but in order to avoid color distortion we usually convert images to HSI, _equalize the intensity channel_ and eventually increase the saturation to correct the perceived loss of vibrancy.

We can apply **smoothing and sharpening on colors**: linear convolutions can be performed channel-wise (e.g. across RGB/CMY) or restricted to the intensity channel in spaces like HSI/YUV for parallelized and efficient image filtering.

**Chroma keying** consists in detecting a known background color (typically green or blue due to camera sensitivities and high contrast with human skin tones) in a specific color space and rendered transparent to composite video frames.
