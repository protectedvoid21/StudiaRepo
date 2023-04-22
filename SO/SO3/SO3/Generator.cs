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

    public static int[] GetRequests(int count, int maxInclusive) {
        int[] requests = new int[count];

        Random random = new();
        for (int i = 0; i < requests.Length; i++) {
            requests[i] = random.Next(1, maxInclusive + 1);
        }

        return requests;
    }
}