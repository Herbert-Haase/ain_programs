# Parse the provided Valgrind lackey memory trace, convert addresses to page numbers,
# simulate LRU cache for varying sizes, and plot hit-rate vs cache size.
import re
from collections import OrderedDict
import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator

# Provided trace (short excerpt from user)
trace_text = """
I  049355a8,3
I  049355ab,1
 L 1ffefffbf0,8
I  049355ac,2
 L 1ffefffbf8,8
I  049355ae,2
 L 1ffefffc00,8
I  049355b0,2
 L 1ffefffc08,8
I  049355b2,1
 L 1ffefffc10,8
I  049355b3,1
 L 1ffefffc18,8
I  048e4d2a,5
I  048e4c2e,3
I  048e4c31,5
 S 1ffefffc18,8
I  049890d0,4
I  049890d4,7
 L 04aaccf0,8
I  049890db,2
I  049890e1,5
I  049890e6,2
"""

# parse addresses: lines with format "<type>  addr,len"
addrs = []
for line in trace_text.strip().splitlines():
    m = re.search(r'([0-9a-fA-F]+),\d+', line)
    if m:
        addr = int(m.group(1), 16)
        addrs.append(addr)

# convert to page numbers (page size 4KiB)
PAGE_BITS = 12
page_nums = [addr >> PAGE_BITS for addr in addrs]

# show mapping
pairs = list(zip(addrs, page_nums))
print("Parsed references (hex addr -> page number):")
for a,p in pairs:
    print(f"0x{a:08x} -> {p}")

# simulate LRU hit rate for cache sizes 1..N
def lru_hits(pages, capacity):
    cache = OrderedDict()
    hits = 0
    for p in pages:
        if p in cache:
            hits += 1
            cache.move_to_end(p)
        else:
            if len(cache) >= capacity:
                cache.popitem(last=False)
            cache[p] = True
    return hits

unique_pages = sorted(set(page_nums))
max_capacity = max(1, len(unique_pages)+2)
sizes = list(range(1, max_capacity+1))
hits = [lru_hits(page_nums, c) for c in sizes]
hit_rates = [h/len(page_nums) for h in hits]

# Also compute the working set size over the whole trace: number of distinct pages seen over prefixes
working_set_prefix = []
seen = set()
for i,p in enumerate(page_nums, start=1):
    seen.add(p)
    working_set_prefix.append(len(seen))

# Plot hit rate vs cache size and working set growth over time
fig, ax1 = plt.subplots(figsize=(7,4))
ax1.plot(sizes, [r*100 for r in hit_rates], marker='o')
ax1.set_xlabel("Cache size (number of pages)")
ax1.set_ylabel("LRU hit rate (%)")
ax1.set_xticks(sizes)
ax1.xaxis.set_major_locator(MaxNLocator(integer=True))
ax1.grid(True, axis='y', linestyle='--', alpha=0.6)

# secondary plot: working set growth as inset
ax2 = fig.add_axes([0.55, 0.55, 0.35, 0.35])
ax2.plot(range(1, len(working_set_prefix)+1), working_set_prefix, marker='o', markersize=4)
ax2.set_title("Working set growth (prefixes)")
ax2.set_xlabel("Reference index")
ax2.set_ylabel("Unique pages seen")
ax2.grid(True, linestyle='--', alpha=0.6)

plt.tight_layout()
# plt.savefig('/mnt/data/trace_cache_analysis.png')
# '/mnt/data/trace_cache_analysis.png'
plt.show()

