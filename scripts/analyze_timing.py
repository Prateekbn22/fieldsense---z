import re
import statistics
import sys
from pathlib import Path

INTERVAL_RE = re.compile(
    r"\[TIME\] interval_ms=(\d+), min_ms=(\d+), max_ms=(\d+), "
    r"mean_ms=(\d+), scheduler_delay_ms=(-?\d+), missed_deadlines=(\d+)"
)

def main() -> int:
    if len(sys.argv) < 2:
        print("Usage: python scripts/analyze_timing.py results/logs/timing_run.txt")
        return 2

    log_path = Path(sys.argv[1])
    if not log_path.exists():
        print(f"Log file not found: {log_path}")
        return 1

    intervals = []
    missed_counts = []

    for line in log_path.read_text(errors="replace").splitlines():
        match = INTERVAL_RE.search(line)
        if match:
            intervals.append(int(match.group(1)))
            missed_counts.append(int(match.group(6)))

    if not intervals:
        print("No [TIME] interval lines found.")
        return 1

    print(f"Samples with interval data: {len(intervals)}")
    print(f"Minimum interval ms: {min(intervals)}")
    print(f"Maximum interval ms: {max(intervals)}")
    print(f"Mean interval ms: {statistics.mean(intervals):.2f}")
    print(f"Final missed deadline count: {missed_counts[-1] if missed_counts else 0}")

    try:
        import matplotlib.pyplot as plt
    except ImportError:
        print("matplotlib not installed, skipping plot.")
        return 0

    output_dir = Path("results/plots")
    output_dir.mkdir(parents=True, exist_ok=True)
    output_path = output_dir / "sample_intervals.png"

    plt.figure()
    plt.plot(range(1, len(intervals) + 1), intervals, marker="o")
    plt.xlabel("Interval index")
    plt.ylabel("Sample interval ms")
    plt.title("FieldSense-Z measured sample intervals")
    plt.grid(True)
    plt.savefig(output_path, dpi=150, bbox_inches="tight")

    print(f"Plot saved to: {output_path}")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())