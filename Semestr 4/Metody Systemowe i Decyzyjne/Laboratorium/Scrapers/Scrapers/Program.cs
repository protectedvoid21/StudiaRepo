using System.Data.SqlClient;
using System.Net.Http.Json;
using System.Text;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Scrapers;

var connectionString =
    "Server=(localdb)\\Local;Database=JobOffers;Trusted_Connection=True;MultipleActiveResultSets=true";

var httpClient = new HttpClient();
var connection = new SqlConnection(connectionString);
connection.Open();

var host = new HostBuilder()
    .ConfigureServices(services =>
    {
        services.AddSingleton(httpClient);
        services.AddSingleton(connection);
        services.AddSingleton<DatabaseService>();
        services.AddSingleton<NflScraper>();
    })
    .Build();
    
    
var scraper = host.Services.GetRequiredService<NflScraper>();
await scraper.ScrapeNflOffers();