import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import re


def build_data_set(content):
    time = []
    impl = []
    for curType in ["Fast", "Slow"]:
        values = re.findall(rf"Time using the {curType} class\s+(.+) \(ms\)", content)
        impl += [curType for _ in values]
        time += [float(t) for t in values]
    df = pd.DataFrame()
    df["Implementation"] = impl
    df["Run time (ms)"]  = time
    return df


def main():
    input_file = "build/m_cache_oop_spatial.txt"
    output_img = "docs/m_cache_oop_spatial.png"

    with open(input_file, "r") as result:
        content = result.read()

    df = build_data_set(content)
    #print(df)

    sns.set_style("dark")
    sns.set_context("talk")

    sns.displot(df, x="Run time (ms)", hue="Implementation",bins=30)#, kind="kde")
    #plt.show()
    plt.savefig(output_img, dpi=400)


main()

