All the techniques discussed in this course make **no usage of machine learning**, geometry still matters nowadays:
- _Measurable uncertainty_: errors can be modeled, propagated and certified
- _Traceability_: auditable pipelines compatible with ISO/VDI standards
- _Interpretability_: parameters with physical meaning
- _Precision_: sub-pixel accuracy with known noise models
- _Reliability_: predictable, detectable failure modes
- _Data-free_: works without training sets
- _Foundation_: modern (including learned) 3D vision is built on, and evaluated with, geometry

There are **3 levels of vision**:
1. _Low (image)_: noise reduction, edge detection
2. _Medium (shapes, regions)_: segmentation, shape recognition
3. _High (concepts)_: scene understanding

Giving a **symbolic description** of the contents of an image (read: image understanding) is difficult because is intrinsically an **inverse problem**:
- We want to recover some unknowns given _insufficient information_ to fully specify the solution
- We must resort to physic-based and/or probabilistic-based models to disambiguate _potential solutions_

In **computer graphics** the transformation of a 3D object into an image, implies information loss, in computer vision we **need models** to retrieve the lost information, which should describe how:
- Objects move
- Lights reflects from object surfaces
- Shapes get projected to the sensor image plane

