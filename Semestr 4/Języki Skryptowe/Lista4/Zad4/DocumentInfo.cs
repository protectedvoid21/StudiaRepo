public record DocumentInfo(
    string FilePath,
    int CharacterCount,
    int WordCount,
    int LineCount,
    char MostOccurrentChar,
    string MostOccurrentWord);