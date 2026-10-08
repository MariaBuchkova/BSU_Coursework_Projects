# Image Inspector

A lightweight WPF application for exploring image files and their technical properties.

Image Inspector lets you select a folder, scan its images, inspect their metadata, and preview files without opening them individually. It was built to understand how common image formats store their information rather than relying on high-level image libraries.

## Features

* Scan a selected folder for supported image files 
* Optionally include subdirectories 
* Detect PNG, JPEG, GIF, BMP, TIFF and PCX files 
* Read image dimensions, color depth, DPI and compression 
* Preview selected images 
* Support animated GIF previews

## Multithreading

The application keeps its window responsive by never doing heavy work on the UI thread. Only the UI thread may touch controls, so everything else runs on the thread pool. Values needed from controls, such as the subdirectories option, are read before the background work starts.

A scan runs in two stages. The folder is first enumerated inside `Task.Run`, with `await` releasing the UI thread meanwhile. The files are then processed with `Parallel.For`, limited to 8 threads so the disk is not flooded, and wrapped in `Task.Run` because `Parallel.For` blocks its caller.

No locks are needed: each iteration writes only to its own slot of the results array, the progress counter uses `Interlocked.Increment`, and every file has its own `FileStream`.

The UI thread polls the counter every 100 ms to show progress. Cancellation is cooperative: pressing Stop signals a `CancellationToken`, no new files are started, files already in progress finish, and the results collected so far are displayed.

This makes the scan suitable for large folders while keeping the interface responsive throughout the operation.

## Format Analysis

The interesting part of the project is the parser.

Instead of treating every image as a black box, the application reads the binary structure of each supported format and extracts the information it needs.

Different formats require different approaches. PNG and JPEG store their metadata in different structures, TIFF introduces byte-order handling and tag-based directories, while BMP, GIF and PCX expose their basic properties directly through their headers.

The parser first checks the file signature to determine the format and then passes the stream to the matching format-specific reader. The results are converted into a common `Row` model, so the UI does not need to know how a particular format stores its metadata.

The supported formats are handled independently, which also makes the parser easier to extend with another format later.

## Format Metadata

The parser reads different parts of each image format depending on how its metadata is encoded.

| Format   | Size                      | Depth                           | DPI              | Compression                |
| -------- | ------------------------- | ------------------------------- | ---------------- | -------------------------- |
| **PNG**  | IHDR width & height       | Bit depth × channels            | pHYs chunk       | Deflate                    |
| **JPEG** | SOF marker                | Precision × components          | JFIF density     | Baseline / Progressive DCT |
| **GIF**  | Logical Screen Descriptor | Color table depth               | —                | LZW                        |
| **BMP**  | DIB header width & height | Bits per pixel                  | Pixels per meter | BI_RGB / RLE / Bitfields   |
| **TIFF** | IFD tags `256`, `257`     | BitsPerSample × SamplesPerPixel | Resolution tags  | TIFF compression tag       |
| **PCX**  | Image bounds in header    | Bits per pixel × planes         | Header DPI       | RLE                        |

The parser reads these values directly from the file structure instead of decoding the complete image. This makes metadata inspection lightweight and also demonstrates how the same properties are represented differently across image formats.

For example, TIFF requires handling both little-endian and big-endian byte order, while JPEG requires walking through its markers to find the relevant SOF and JFIF information. PNG stores its basic image information in the IHDR chunk and resolution in a separate pHYs chunk.

## Scanning

Image files are discovered first and then processed in parallel. Scanning can be recursive, and inaccessible directories are ignored instead of stopping the entire operation.

The application also keeps the scan state explicit: while processing, the folder button is disabled, the Stop button becomes available, and the progress bar reflects the number of files already handled.

If a file cannot be parsed, the scan does not have to fail as a whole. Parsing errors are associated with the corresponding result, allowing the rest of the collection to continue being inspected.

## Preview

Selecting an image displays its preview alongside the metad