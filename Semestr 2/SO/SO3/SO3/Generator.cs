namespace SO3; 

public static class Generator {
    public static Page[] GetPages(int count) {
        Page[] pages = new Page[count];

        for (int i = 0; i < pages.Length; i++) {
            pages[i] = new Page();
        }

        return pages;
    }

    public static Page[] CopyPages(Page[] pages) {
        return pages.Select(p => new Page()).ToArray();
    }

    public static int[] GetRequests(int count, int maxInclusive, int localChancePercentage, int minLocalCount, int maxLocalCount) {
        int[] requests = new int[count];

        Random random = new();
        int lastRequest = 1;
        for (int i = 0; i < requests.Length; i++) {
            if (random.Next(100) < localChancePercentage) {
                if (lastRequest == 1) {
                    lastRequest++;
                }

                int localCount = random.Next(minLocalCount, maxLocalCount + 1);
                for (int j = 0; j < localCount; j++) {
                    if (i == requests.Length) {
                        return requests;
                    }
                    requests[i] = random.Next(lastRequest - 1, lastRequest + 1);
                    i++;
                }
            }
            else {
                requests[i] = random.Next(1, maxInclusive + 1);
                lastRequest = requests[i];
            }
        }

        return requests;
    }
}