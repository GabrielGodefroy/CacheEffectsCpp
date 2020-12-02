import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import re


def build_data_set(content, types=["char", "short", "int", "double"]):
    df = pd.DataFrame()
    for t in types:
        print(t)
        values = re.findall(rf"Touching every (.+) index on type (.+) (.+) \(ms\)", content)
        step = [float(t[0]) for t in values]
        value_type = [str(t[1]) for t in values]
        time = [float(t[2]) for t in values]
        df["step"] = step
        df["Value type"] = value_type
        df["Run time (ms)"] = time
    return df


def main():
    input_file = "build/m_cache_lines.txt"
    output_img = "docs/m_cache_lines.png"

    with open(input_file, "r") as result:
        content = result.read()

    df = build_data_set(content)

    sns.lineplot(data=df, x="step", y="Run time (ms)",hue="Value type",ci=None,linewidth=1.0)

    plt.axvline(16, color="red",linewidth=0.8)
    plt.axvline(32, color="green",linewidth=0.8)
    plt.axvline(64, color="orange",linewidth=0.8)
    plt.axvline(128, color="blue",linewidth=0.8)

    #plt.title("Example Plot")
    #plt.ylabel("Run time in ms")
    #plt.xlabel("Spacing between accessed elements (delta)")

    plt.legend()

    plt.xscale("symlog")
    plt.xticks(
        [0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512],
        [0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512],
    )
    plt.xlim([-0.5, df['step'].max()])
    # plt.ylim([0,16])
    plt.savefig(output_img, dpi=400)


main()

