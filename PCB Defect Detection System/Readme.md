
# PCB Defect Detection System using YOLOv8

This project presents a real-time **Printed Circuit Board (PCB) defect detection system** leveraging the **YOLOv8** deep learning model, trained on a comprehensive dataset and deployed on a **Raspberry Pi** for practical use on production lines.

---

## Overview

With the growing dependency on PCBs in electronic devices, ensuring their quality is critical. Manual inspection is prone to error, allowing defects to go unnoticed and potentially leading to product failure.

This system automates PCB inspection on a production line by:
- Detecting surface defects using a deep learning model
- Sorting defective PCBs for repair or reuse
- Performing real-time analysis via livestream on an embedded platform

---

##  Key Features

-  Real-time defect detection
-  Based on state-of-the-art **YOLOv8** architecture
-  Trained on the **TDD-Net dataset**
-  Handles **6 surface defect types**
-  High accuracy: **84.38% accuracy** and **98.4% mAP**
-  Deployed on **Raspberry Pi** for embedded processing

---

##  Dataset

- **TDD-Net Dataset**
  - Contains a wide range of PCB layouts
  - Includes annotated images with 6 distinct surface defects
  - Used for training, validation, and testing of YOLO models

---

## Model Development

- Compared different YOLO versions and trade-offs
- YOLOv8 selected based on highest accuracy and performance
- Model trained and evaluated rigorously on defect classes

---

##  Deployment

- Final YOLOv8 model deployed on **Raspberry Pi**
- Integrated with camera feed for **continuous livestream monitoring**
- Designed for integration into **production environments**

---

##  Applications

- Quality assurance in PCB manufacturing
- Automated visual inspection
- Real-time fault detection in industrial automation

---

##  Technologies Used

- YOLOv8 (Ultralytics)
- Python
- OpenCV
- TDD-Net Dataset
- Raspberry Pi (for deployment)



