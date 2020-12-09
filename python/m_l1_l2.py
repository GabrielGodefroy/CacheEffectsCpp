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
    values = re.findall(r"([0-9]+)\s+(.+)", content)
    size = [float(t[0]) for t in values]
    time = [float(t[1]) for t in values]

    df["size"] = size
    df["Run time (ms)"] = time
    return df

def main():
    input_file = "build/m_l1_l2.txt"
    output_png = "docs/m_l1_l2.png"

    sns.set_style("dark")
    sns.set_context("talk")

    plt.axvline(32000, color="lightgreen", linewidth=2)
    plt.axvline(256000, color="orange", linewidth=2)
    plt.axvline(4000000, color="lightblue", linewidth=2)

    df = load_file_as_dataframe(input_file)
    sns.scatterplot(data=df, x="size", y="Run time (ms)", alpha=0.3, s = 25)
    df = df.groupby("size").mean()
    sns.lineplot(data=df, x="size", y="Run time (ms)")

    plt.xscale("log")
    plt.xticks(
        [2**10, 2**15, 2**17, 2**22, 128000000],
        ["2^10", "2^15", "2^17", "2^22", "128M"],
    )
    plt.ylim([0, 1.15 * df["Run time (ms)"].max()])

    plt.tight_layout()
    plt.savefig(output_png, dpi=400)
    #plt.show()

if __name__ == "__main__":
    main()
