using System.Data.SqlClient;
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
        services.AddSingleton<PracujScraper>();
    })
    .Build();


var scrapers = new IScraper[]
{
    // host.Services.GetRequiredService<NflScraper>(),
    host.Services.GetRequiredService<PracujScraper>()
};

foreach (var scraper in scrapers)
{
    await scraper.RunAsync();
}