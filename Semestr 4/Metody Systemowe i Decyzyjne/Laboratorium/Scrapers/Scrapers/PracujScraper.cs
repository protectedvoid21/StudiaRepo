using System.Text.Json;
using System.Text.RegularExpressions;

namespace Scrapers;

public class PracujScraper(HttpClient httpClient, DatabaseService databaseService) : IScraper
{
    private const string BaseUrl = "https://www.pracuj.pl/praca/it%20-%20rozwój%20oprogramowania;cc,5016/programowanie;cc,5016003";
    private const string SalaryRegex = @"\d+";
    private const int HoursInMonth = 168;
    private const int HourSalaryThreshold = 300;
    
    public async Task RunAsync()
    {
        for (int i = 1; i < 100; i++)
        {
            var response = await httpClient.GetAsync(GetOfferPageUrl(i));
            
            if (!response.IsSuccessStatusCode)
            {
                Console.WriteLine($"Failed to fetch page {i}");
                return;
            }
            
            var content = await response.Content.ReadAsStringAsync();
            var pracujResponse = JsonSerializer.Deserialize<PracujResponse>(GetOfferJson(content));
            
            if (pracujResponse is null)
            {
                Console.WriteLine($"Failed to deserialize page {i}");
                return;
            }
            
            foreach(var offer in pracujResponse.props.pageProps.data.jobOffers.groupedOffers)
            {
                databaseService.AddOffer(MapPracujResponseToOfferDto(offer));
                Console.WriteLine($"Added offer {offer.jobTitle}");
            }
        }
    }
    
    public static Tuple<int, int> GetSalaryFromText(string salaryText)
    {
        salaryText = salaryText.Replace(" ", string.Empty).Replace("\u00a0", string.Empty);
        var regex = new Regex(SalaryRegex);
        var match = regex.Matches(salaryText);
        
        if (match.Count == 0)
        {
            return new Tuple<int, int>(0, 0);
        }

        if (!int.TryParse(match[0].Value, out var from))
        {
            Console.WriteLine("Failed to parse SalaryTo from text");
            return new Tuple<int, int>(0, 0);
        }

        if (match.Count == 1)
        {
            return new Tuple<int, int>(from, from);
        }

        if (!int.TryParse(match[1].Value, out var to))
        {
            Console.WriteLine("Failed to parse SalaryFrom from text");
            return new Tuple<int, int>(0, 0);
        }

        return new Tuple<int, int>(from, to);
    }
    
    private static string GetOfferPageUrl(int pageIndex) => $"{BaseUrl}?pn={pageIndex}";

    private static string GetOfferJson(string htmlContent)
    {
        var regex = new Regex("<script id=\"__NEXT_DATA__\" type=\"application/json\">(.*?)</script>");
        
        var match = regex.Match(htmlContent);
        
        return match.Success ? match.Groups[1].Value : string.Empty;
    }
    
    private static OfferDto MapPracujResponseToOfferDto(PracujOffer offer)
    {
        var (salaryFrom, salaryTo) = GetSalaryFromText(offer.salaryDisplayText);
        
        if (salaryTo < HourSalaryThreshold)
        {
            salaryFrom *= HoursInMonth;
            salaryTo *= HoursInMonth;
        }

        return new OfferDto
        {
            Name = offer.jobTitle,
            SalaryFrom = salaryFrom,
            SalaryTo = salaryTo,
            ExpLevel = string.Join(' ', offer.positionLevels),
            CompanyName = offer.companyName,
            OfferPortalId = 4,
            Category = "TODO",
            JobLanguage = "pl",
            Location = offer.offers[0].displayWorkplace,
            IsRemote = offer.offers.Any(o => o.displayWorkplace.Contains("zdalna", StringComparison.InvariantCultureIgnoreCase)),
            Technology = "",
            ExternalId = offer.groupId
        };
    }
}