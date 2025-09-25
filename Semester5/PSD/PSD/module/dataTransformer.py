import pandas as pd
import numpy as np

def combineData(data1, data2):
    data = np.hstack((np.array(data1), np.array(data2)))
    return pd.DataFrame(data, columns=["sepal_length", "sepal_width", "petal_length", "petal_width", "species"])
