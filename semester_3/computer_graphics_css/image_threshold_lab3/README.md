# Image Threshold & Processing Lab

A lightweight WPF application for image processing, point operations, and advanced thresholding (binarization) methods.

Image Threshold lets you load images, adjust their brightness, gamma, and contrast, and apply both global and local thresholding algorithms directly on raw pixel buffers[cite: 2, 3, 4, 5]. It was built to understand how low-level image manipulation, multithreading, and binary structure processing work under the hood without relying on heavy external image processing suites[cite: 2, 3, 4, 5].

## Features

- Load and save standard image formats (PNG, JPEG, BMP)[cite: 3]
- Apply point operations: brightness adjustment, gamma correction, and negative inversion[cite: 4]
- Perform automatic linear histogram contrast stretching[cite: 4]
- Convert full-color BGRA images to grayscale using psycho-physiological weights[cite: 2]
- Apply global thresholding methods: Otsu's method and Iterative thresholding[cite: 5]
- Apply local adaptive thresholding (Sauvola's method) using integral images for high-speed performance[cite: 5]
- Support flexible boundary modes (`Clamp` and `Reflect`) for window-based operations[cite: 2]

## Pipeline & Architecture

The project is structured into dedicated, modular components to separate memory management from mathematical algorithms:

- **`ImageBuffer` & `GrayBuffer`**: Manage raw byte arrays (`byte[]`) for 32-bit BGRA and 8-bit grayscale formats, handling memory allocation and row strides (`Width * 4`)[cite: 2].
- **`PointOps`**: Implements element-wise transformations through Lookup Tables (LUTs) and histogram analysis for contrast manipulation.
- **`Thresholding`**: Contains global optimization algorithms and local adaptive thresholding powered by integral images for $O(1)$ box-filter calculations.

## Algorithm Summary

| Module / Method | Purpose | Key Mechanics |
| --------------- | ------- | ------------- |
| **ToGray** | Color to Grayscale conversion[cite: 2] | Uses human perception weights: $0.114B + 0.587G + 0.299R$ via unsafe pointers |
| **Linear Contrast** | Dynamic range stretching | Analyzes brightness histogram, clips noise by percentage, and stretches range to `[0, 255]`|
| **Otsu** | Global automatic binarization | Maximizes inter-class variance across all possible thresholds from $0$ to $255$|
| **Iterative** | Threshold optimization | Recursively splits histogram into two classes until threshold convergence |
| **Adaptive (Sauvola)** | Local thresholding| Uses **integral images** to compute local mean and standard deviation in $O(1)$ time |

## Boundary Handling

When performing neighborhood-based operations (like adaptive thresholding), pixels near the edges require special care. The `GrayBuffer.Padded` and `EdgeMode` mechanisms handle this seamlessly:
- **`Clamp`**: Extends border pixels outward.
- **`Reflect`**: Mirrors image content across boundaries to eliminate edge artifacts.