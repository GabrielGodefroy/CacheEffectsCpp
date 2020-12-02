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
    
    return df


def plot_zoom(df, png_name):
    fig, axes = plt.subplots(1, 3, sharey=True, figsize=(8, 4))

    axes_xlim = [[0, 20], [502, 522], [1014, 1034]]
    for ax_ind, ax in enumerate(axes):
        sns.lineplot(
            data=df,
            x="step",
            y="Run time (ms)",
            hue="Array size",
            marker=".",
            ax=ax,
            ci=None,
            linewidth=0.8
        )

        ax.set_ylim(0.95*df["Run time (ms)"].quantile(0.05),df["Run time (ms)"].quantile(0.99))
        ax.set_xlim(axes_xlim[ax_ind])
        if(ax_ind>0):
            ax.get_legend().remove()

    fig.suptitle("Zoom on some values")

    #axes[0].set_ylim([0.05, 0.50])
    
    plt.savefig(png_name, dpi=400)


def plot_all(df, png_name):
    sns.lineplot(
        data=df, x="step", y="Run time (ms)", hue="Array size",linewidth=0.8, marker=None, ci=None
    )
    plt.title("Run time to access every i element of an array")
    plt.xscale("symlog")
    plt.xticks(
        [0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024],
        [0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024],
    )
    plt.xlim([0, 1200])
    plt.ylim(0.95*df["Run time (ms)"].quantile(0.05),df["Run time (ms)"].quantile(0.99))

    # plt.ylim([0.05, 0.50])
    plt.savefig(png_name, dpi=400)


def main():
    input_file = "build/m_cache_associativity.txt"
    output_img = "docs/m_cache_associativity.png"
    output_zoom_img = "docs/m_cache_associativity_zoom.png"

    df = load_file_as_dataframe(input_file)

    sns.set_palette("hls", 6)

    plot_zoom(df, output_zoom_img)
    plt.cla()
    plt.clf()
    plot_all(df, output_img)
    plt.cla()


main()

