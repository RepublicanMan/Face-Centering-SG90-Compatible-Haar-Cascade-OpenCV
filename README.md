# Face-Centering-SG90-Compatible-Haar-Cascade-OpenCV

Hi, my name is Justin. This repository contains the source code for my project, with a focus on real-time face tracking, visualization, and servo-based gimbal control. The project explores and compares two different computer vision approaches: a deep-learning-based YOLOv8 pipeline and a classical OpenCV Haar Cascade pipeline.

Group Members: 
Paul Kenneth Castillo Andes
2702389606
Makaio Wimylie
2702281203
Justin Jeremiah Hendrajudo
2702406221
Justin Lee
2702406221

Lecturer: D7040 - RICKY REYNARDO SISWANTO, S.T., M.Kom.

Note: The YOLOv8 model provided in this repository has already been trained. If you want to retrain the model, you need to train it manually using your own environment.

---

## Machine Learning and Computer Vision Approach

1. YOLOv8-Based Detection (Initial Approach)

The project initially used a YOLOv8-based detection pipeline for face or person detection. YOLOv8 is a modern deep-learning object detection model capable of high detection accuracy and robustness. The model was trained using a custom dataset and integrated into a real-time video processing loop.

The model was trained using the following command, executed directly in the terminal from the project’s main directory (with the correct path already set):

yolo detect train model=best.pt epochs=100 imgsz=640 batch=16 device=0 workers=0 cache=True

Explanation of parameters:

* model=yolov8s.pt specifies the base YOLOv8 model
* data=.../data.yaml points to the dataset configuration file
* epochs=100 defines the number of training epochs
* imgsz=640 sets the input image resolution
* batch=16 determines the batch size
* device=0 selects the GPU for training
* workers=0 disables multiprocessing to avoid Windows-related issues
* cache=True enables dataset caching to speed up training

Although YOLOv8 successfully detected targets and produced bounding boxes, the integration with the servo control loop was not reliable in practice. Due to inference overhead and inconsistent update timing, the control system did not receive sufficiently stable and continuous position data, resulting in little to no servo movement.

2. OpenCV + Haar Cascade Detection (Final Approach)

To achieve reliable real-time control, the detection system was redesigned using OpenCV’s Haar Cascade face detector. Haar Cascades are classical computer vision algorithms that operate efficiently on grayscale images and provide fast, deterministic detections.

In this implementation:

* Frames are converted to grayscale for faster processing
* Haar Cascade detects faces on a per-frame basis
* The face closest to the previously tracked position is selected to maintain tracking stability
* The detected face center is used to compute positional error relative to the image center

This approach produces low-latency, frame-consistent detections, which allows the control loop to generate smooth and continuous error signals. As a result, the servo-driven gimbal responds correctly, enabling stable face tracking, automatic recentering when the target is lost, and smooth motion behavior similar to a stabilized targeting system.

Summary

While YOLOv8 provides advanced deep-learning-based detection, the OpenCV Haar Cascade approach proved more suitable for this real-time embedded control application. The final system prioritizes responsiveness, deterministic behavior, and control-loop stability over detection model complexity, resulting in a functional and reliable servo-tracking solution.
