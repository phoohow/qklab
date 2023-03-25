import cv2
import numpy as np

# 定义平面参数
plane_normal = np.array([1, 1, 1], dtype=np.float64)
plane_point = np.array([1, 0, 0], dtype=np.float64)
# 定义待投影点
point = np.array([1, 2, 1], dtype=np.float64)
# 计算点到平面的投影
projection, jacobian = cv2.projectPoints(
    point.reshape(-1, 1, 3),
    plane_normal.reshape(-1, 3),
    plane_point.reshape(-1, 3),
    np.eye(3),
    np.zeros(5),
)
# 输出投影结果
print(projection)
