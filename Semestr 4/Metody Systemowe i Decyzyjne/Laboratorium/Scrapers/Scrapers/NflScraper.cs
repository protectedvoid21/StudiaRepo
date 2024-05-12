using System.Data.SqlClient;
using System.Net.Http.Json;

namespace Scrapers;

public class NflScraper(HttpClient httpClient, SqlConnection connection, DatabaseService databaseService)
{
    public async Task ScrapeNflOffers()
    {
        int counter = 0;
        const int offersToScrape = 100;
        
        for (int i = 0; i < 100; i++)
        {
            var nflRequest = new NflRequest(i, offersToScrape, true);
            var nflResponse = await GetNflResponses(nflRequest, httpClient);
            
            Console.WriteLine();

            counter += nflResponse.Postings.Length;
            Console.WriteLine($"Scraped {nflResponse.Postings.Length} offers");
            Console.WriteLine($"Total scraped offers: {counter}");

            if (nflResponse.Postings.Length == 0)
            {
                return;
            }
            
            foreach (var posting in nflResponse.Postings)
            {
                databaseService.AddOffer(GetOfferDto(posting));
            }
        }
    }

    private static OfferDto GetOfferDto(Posting posting)
    {
        return new OfferDto
        {
            Name = posting.Name,
            SalaryFrom = posting.Salary.From,
            SalaryTo = posting.Salary.To,
            ExpLevel = string.Join(", ", posting.Seniority),
            Category = posting.Category,
            JobLanguage = string.Join(", ", posting.Tiles.Values
                .Where(v => v.Type.Equals("joblanguage", StringComparison.InvariantCultureIgnoreCase))
                .Select(v => v.Value)),
            Location = GetLocations(posting.Location),
            IsRemote = posting.FullyRemote,
            Technology = posting.Technology,
            ExternalId = posting.Posted.ToString(),
            CompanyName = posting.Name,
            OfferPortalId = 2
        };
    }
    
    private static string GetLocationSelector(Places place)
    {
        List<Func<Places, string>> selectors =
        [
            p => p.City,
            p => p.Province,
            p => p.Country.Name
        ];

        foreach (var selector in selectors)
        {
            var location = selector(place);
            if (!string.IsNullOrEmpty(location))
            {
                return location;
            }
        }

        return "N/A";
    }

    private static async Task<NflResponse> GetNflResponses(NflRequest nflRequest, HttpClient httpClient)
    {
        var url =
            $"https://nofluffjobs.com/api/joboffers/main?pageTo={nflRequest.PageTo}&pageSize={nflRequest.PageSize}&withSalaryMatch={nflRequest.WithSalaryMatch}&salaryCurrency=PLN&salaryPeriod=month&region=pl";

        var httpRequest = await httpClient.GetAsync(url);
        var nflResponse = await httpRequest.Content.ReadFromJsonAsync<NflResponse>();

        return nflResponse;
    }

    private static string GetLocations(Location location)
    {
        return string.Join(", ", location.Places.Select(GetLocationSelector));
    }
}