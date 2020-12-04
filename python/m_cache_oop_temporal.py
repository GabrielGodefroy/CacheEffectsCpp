import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import re


def build_data_set(content):
    time = []
    impl = []
    for temp_loc in ["On", "Off"]:
        values = re.findall(rf"Temporal locality is {temp_loc}\s+(.+) \(ms\)", content)
        impl += [temp_loc for _ in values]
        time += [float(t) for t in values]
    df = pd.DataFrame()
    df["Temporal locality"] = impl
    df["Run time (ms)"]  = time
    return df


def main():
    input_file = "build/m_cache_oop_temporal.txt"
    output_img = "docs/m_cache_oop_temporal.png"

    with open(input_file, "r") as result:
        content = result.read()

    df = build_data_set(content)
    print(df)

    sns.set_style("dark")
    sns.set_context("talk")

    sns.displot(df, x="Run time (ms)", hue="Temporal locality",kind="kde")

    plt.axvline(df[df["Temporal locality"]=="Off"]["Run time (ms)"].mean(), color="orange",linewidth=1.5)
    plt.axvline(df[df["Temporal locality"]=="On"]["Run time (ms)"].mean(), color="blue",linewidth=1.5)

    #plt.show()
    plt.savefig(output_img, dpi=400)


main()

