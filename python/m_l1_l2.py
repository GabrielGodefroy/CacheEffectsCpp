import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import re


def load_file_as_dataframe(input_file):
    with open(input_file, "r") as result:
        content = result.read()
    df = build_data_set_from_text(content)
    return df


def build_data_set_from_text(content):
    df = pd.DataFrame()
    values = re.findall(r"Step: (.+); Size: (.+); Time: (.+) ms", content)
    step = [float(t[0]) for t in values]
    size = [float(t[1]) for t in values]
    time = [float(t[2]) for t in values]

    df["step"] = step
    df["Array size"] = size
    df["Run time (ms)"] = time

    df["Array size"] = df["Array size"]/1024
    df = df.astype({"Array size": int})
    df = df.astype({"Array size": str})
    