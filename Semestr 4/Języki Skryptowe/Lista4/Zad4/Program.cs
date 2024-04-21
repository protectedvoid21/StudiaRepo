using System.Text.Encodings.Web;
using System.Text.Json;

string? filePath = Console.ReadLine();

if (string.IsNullOrEmpty(filePath))
{
    Console.WriteLine("File path was not provided!");
    return;
}

if(!File.Exists(filePath))
{
    Console.WriteLine("File does not exist!");
    return;
}

int characterCount = 0;
int wordCount = 0;
int lineCount = 0;

var characterOccurenceDictionary = new Dictionary<char, int>();
var wordOccurenceDictionary = new Dictionary<string, int>();

var fileLines = File.ReadLines(filePath);

foreach (var line in fileLines)
{
    characterCount += line.Length;
    lineCount++;
    var splitLine = line.Split([',', ';', '.', '!', '?', '<', '>', '\\', ':', '\'', '[', ']', '{', '}', '|', ' ']);
    foreach (var word in splitLine)
    {
        if (string.IsNullOrWhiteSpace(word))
        {
            continue;
        }
        if (!wordOccurenceDictionary.TryAdd(word, 1))
        {
            wordOccurenceDictionary[word]++;
        }
    }
    
    wordCount += splitLine.Length;
    foreach (var c in line)
    {
        if (!char.IsLetterOrDigit(c))
        {
            continue;
        }
        if (!characterOccurenceDictionary.TryAdd(c, 1))
        {
            characterOccurenceDictionary[c]++;
        }
    }
}

char mostOccurrenceChar = characterOccurenceDictionary.MaxBy(x => x.Value).Key;
string mostOccurrenceWord = wordOccurenceDictionary.MaxBy(x => x.Value).Key;

var documentInfo = new DocumentInfo(filePath, characterCount, wordCount, lineCount, mostOccurrenceChar, mostOccurrenceWord);

var jsonOptions = new JsonSerializerOptions
{
    WriteIndented = args.Contains("--pretty"),
    Encoder = JavaScriptEncoder.UnsafeRelaxedJsonEscaping
};

var jsonText = JsonSerializer.Serialize(documentInfo, jsonOptions);
Console.WriteLine(jsonText);