Morphology offers a unified and powerful approach to numerous image processing problems.

We'll start by considering thresholded images containing only black and white pixels, where the **set of white pixels** contains the complete _morphological description_ of the image.

Such sets are subsets of $\mathbb Z$ where each vector express coordinates of white pixels.
![[Thresholded binary image.png|515]]
**Set translation**
Shifts every point of a set $B$ by a vector $z = (z_1, z_2)$:
$$(B)_z = \{c \mid c = b + z,\ \forall b \in B\}$$
![[Set translation.png|99]]

Each pixel $(x, y)$ becomes $(x + z_1, y + z_2)$.

**Set reflection**
Flips a set about the origin:
$$\hat{B} = \{w \mid w = -b,\ \forall b \in B\}$$
![[Set reflection.png|159]]

Each pixel $(x, y)$ becomes $(-x, -y)$.

Morphological operations are based on so-called **structuring elements (SEs)**, they represent small sets or sub-images used to probe an image under study for properties of interest.
![[SEs.png]]
### Binary morphology

#### Erosion
$$A \ominus B = \{z \mid (B)_z \cap \bar{A} = \emptyset\}$$

In words, the erosion of $A$ by $B$ is the set of all points $z$ such that **$B$, translated to $z$**, is **entirely contained in $A$**. 
>Equivalent to saying the translated $B$ has no overlap with the complement $\bar{A}$.

**How to apply it**
Slide the SE over the image, then at each position, keep the center pixel only if every pixel of the SE lies on a white pixel, if any SE pixel touches background, the center is removed.

![[Erosion example 1.png|316]]
![[Erosion example 2.png|327]]

**Effects**:
- Shrinks objects and removes boundary pixels
- Eliminates details smaller than the SE (thin lines, small blobs)
- Larger SEs erode more

#### Dilation
$$A \oplus B = \{z \mid (\hat{B})_z \cap A \neq \emptyset\}$$
In words, the dilation of $A$ by $B$ is the set of all displacements $z$ such that the reflected SE ($B$) and $A$ **overlap in at least one element**.
>Flipping $B$ and sliding it over $A$ is analogous to spatial convolution.

![[Dilation example 1.png|204]]
![[Dilation example 2.png|425]]

**Effects**:
- Grows/thickens objects
- Simplest use is _bridging gaps_ (e.g., reconnecting broken characters in text).
- Dilating a square of side $d$ with a small square SE enlarges it uniformly, an elongated SE enlarges it more in one direction.

>[!Tip]
>Erosion and dilation are **duals**: eroding the foreground is equivalent to dilating the background (and vice versa).
>>When the SE is symmetric, $\hat{B} = B$.

#### Opening and closing
| |Definition|Meaning|Effects|
|---|---|---|---|
|**Opening**|$A \circ B = (A \ominus B) \oplus B$|Erosion, then dilation|Smooths contours, breaks narrow isthmuses, removes thin protrusions and small bright noise|
|**Closing**|$A \bullet B = (A \oplus B) \ominus B$|Dilation, then erosion|Smooths contours, fuses narrow breaks and long thin gulfs, eliminates small holes, fills gaps in contours|

>[!Tip]
>Both are (nearly) **idempotent**: applying them twice gives the same result as once. 
>Unlike plain erosion/dilation, they **don't permanently shrink or grow** objects, because the second step compensates for the first.

![[Opening and closing example 1.png|442]]
![[Opening and closing example 2.png|450]]

### Grayscale morphology
Erosion, dilation, opening and closing extend to grayscale images.
The SE $b$ can be **flat** (behaves like a shaped neighborhood) or **non-flat** (has height values, like a 3D shape).

#### Erosion (flat SE)
$$f \ominus b = \min_{(s,t)\in b} f(x+s,, y+t)$$
The erosion of an image $f$ by a flat SE $b$ at any location is defined as the **minimum** of the image over the region covered by $b$ centered at $(x,y)$.
>It is similar to an [[03 - Spatial filtering#Order-statistic filters|order-statistic (min) filter]], except that the neighborhood can have any shape.

The effect is that the image gets **darker**, and bright features shrink.

#### Dilation (flat SE)
$$f \oplus b = \max_{(s,t)\in b} f(x-s,, y-t)$$

The dilation of $f$ by a flat structuring element $b$ at any location is defined as the **maximum** of the image over the region covered by the _reflected_ SE (hence the minus signs, from $\hat{b}(x,y) = b(-x,-y)$).

The effect is that the image gets **brighter**, bright features thicken, and dark features are reduced.

#### Opening and Closing (grayscale)
Same formulas as the binary case:  
$$f \circ b = (f \ominus b) \oplus b \qquad f \bullet b = (f \oplus b) \ominus b$$
![[Opening and closing geometric interpretation.png]]

**Geometric interpretation** (treat $f$ as a 3D surface, intensity = height):
- _Opening_: push the SE up from _below_ against the under-surface of $f$, peaks narrower than the SE get cut off (flattened)
- _Closing_: push the SE down from _above_, valleys narrower than the SE get filled in

**Effects**:
- _Opening_: attenuates bright features, with a negligible effect on dark features and background
- _Closing_: attenuates dark features, with a negligible effect on bright features and background

### Applications of grayscale morphology

#### Morphological smoothing
Opening suppresses bright details and closing suppresses dark details, so an **opening–closing sequence** is used for smoothing and noise removal.
![[Morphological smoothing.png]]
#### Morphological gradient
$$g = (f \oplus b) - (f \ominus b)$$
Dilation thickens regions and erosion shrinks them, so their difference highlights **boundaries between regions**.
![[Morphological gradient.png]]

Homogeneous areas cancel out, producing an edge-enhancing, derivative-like result.

#### Top-hat and Bottom-hat
$$T_{hat}(f) = f - (f \circ b) \qquad B_{hat}(f) = (f \bullet b) - f$$
- **Top-hat**: extracts _bright_ objects smaller than the SE (the part removed by opening)
- **Bottom-hat**: extracts _dark_ objects smaller than the SE (the part filled by closing)

The goal is to choose an SE that is too big to fit inside the objects we want to select.
Opening/closing removes them, so the difference isolates exactly those objects.

With uneven illumination, a **global threshold** (e.g. [[02 - Intensity transformations#Histogram for thresholding|Otsu]]) can fail in some regions, the fix is the following one:
1. Open the image with a large SE (e.g. a 40 $\times$ 40 disc) bigger than the objects, this gives an estimate of the background/illumination
2. Subtract it from the original (top-hat), this leaves the objects on a flat background
3. Apply Otsu thresholding, which now gives a clean segmentation

![[Top-hat illumination.png]]
![[Otsu after top-hat.png|562]]

