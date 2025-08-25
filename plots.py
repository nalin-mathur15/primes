import argparse
import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

def loadlineInts(path: Path) -> np.ndarray:
    if not path.exists:
        raise FileNotFoundError(f"Missing file: {path}")
    text = path.read_text().strip()
    if not text:
        return np.array([], dtype=int)
    return np.fromstring(text, dtype=int, sep=',')

def pi_curve(primes: np.ndarray):
    if primes.size == 0:
        return np.array([0]), np.array([0])
    x = primes
    pi = np.arange(1, primes.size + 1)
    return x, pi

def q_count(q: np.ndarray):
    if q.size == 0:
        return np.array([0]), np.array([0])
    x = q
    count = np.arange(1, q.size + 1)
    return x, count

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dir", default=".", help="Directory containing p.csv, q.csv, dq.csv")
    ap.add_argument("--show", action="store_true", help="Show plots interactively")
    args = ap.parse_args()

    d = Path(args.dir)
    p = loadlineInts(d / "p.csv")
    q = loadlineInts(d / "q.csv")
    dq = loadlineInts(d / "dq.csv")

    plt.figure()
    if dq.size > 0:
        bins = min(50, max(5, int(np.sqrt(dq.size))))
        plt.hist(dq, bins=bins)
        plt.title("Gaps between consecutive primes of the form k^2 + 1")
        plt.xlabel("Gap size")
        plt.ylabel("Frequency")
    else:
        plt.title("No gaps: q has < 2 elements")
    out1 = d / "dq_hist.png"
    plt.savefig(out1, dpi=160, bbox_inches="tight")
    if args.show:
        plt.show()
    plt.close()

    x, pi_x = pi_curve(p)
    plt.figure()
    plt.step(x, pi_x, where="post")
    plt.title("Prime Counting Function π(x)")
    plt.xlabel("x")
    plt.ylabel("π(x)")
    out2 = d / "pi_curve.png"
    plt.savefig(out2, dpi=160, bbox_inches="tight")
    if args.show:
        plt.show()
    plt.close()

    qx, qcount = q_count(q)
    plt.figure()
    plt.step(qx, qcount, where="post")
    plt.title("Count of primes of the form k^2 + 1 ≤ x")
    plt.xlabel("x")
    plt.ylabel("count")
    out3 = d / "q_count_curve.png"
    plt.savefig(out3, dpi=160, bbox_inches="tight")
    if args.show:
        plt.show()
    plt.close()

    print(f"Saved: {out1.name}, {out2.name}, {out3.name} in {d.resolve()}")

if __name__ == '__main__':
    main()