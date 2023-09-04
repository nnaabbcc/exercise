
import pydicom
import numpy as np
import cv2

img_file = "data/1/MG-00000836-1.2.826.0.1.3680043.10.279.2.239694255265567868018954853413.tif"
dataset_from = "data/1/MG-00000474-1.2.826.0.1.3680043.10.279.2.255583004994416970822127519736.dcm"
output_dcm = "output/1/MG-00000836.dcm"

img = cv2.imread(img_file, cv2.IMREAD_UNCHANGED)
print(img.shape)
print(img.dtype)

min_value = np.min(img)
max_value = np.max(img)
print(min_value, max_value)

pd = img.tobytes()
print(len(pd))

dcm = pydicom.dcmread(dataset_from)
dcm.PixelData = pd
dcm.save_as(output_dcm)