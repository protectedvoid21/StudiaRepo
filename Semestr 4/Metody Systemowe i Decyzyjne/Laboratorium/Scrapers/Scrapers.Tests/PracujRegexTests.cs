namespace Scrapers.Tests;

public class PracujRegexTests
{
    [Theory]
    [InlineData("1000 - 2000 PLN", 1000, 2000)]
    [InlineData("17000–30000 zł / mies. (zal. od umowy)", 17_000, 30_000)]
    [InlineData("26000–36000złbrutto/mies.", 26_000, 36_000)]
    [InlineData("90–110 zł netto (+ VAT) / godz.", 90, 110)]
    [InlineData("20160–26880zł netto (+ VAT) / mies.", 20_160, 26_880)]
    [InlineData("22050–27550 zł brutto / mies.", 22_050, 27_550)]
    [InlineData("31920–35280zł netto (+ VAT) / mies.", 31_920, 35_280)]
    [InlineData("190zł netto (+ VAT) / godz.", 190, 190)]
    [InlineData("20\u00a0160–26\u00a0880\u00a0zł netto (+\u00a0VAT)\u00a0/ mies.", 20_160, 26_880)]
    [InlineData("22\u00a0050–27\u00a0550\u00a0zł brutto\u00a0/ mies.", 22_050, 27_550)]
    [InlineData("", 0, 0)]
    [InlineData("abcd", 0, 0)]
    public void Parse_GetSalary_ReturnsCorrectTuple(string salaryText, int expectedFrom, int expectedTo)
    {
        var (from, to) = PracujScraper.GetSalaryFromText(salaryText);
        
        Assert.Equal(expectedFrom, from);
        Assert.Equal(expectedTo, to);
    }
}