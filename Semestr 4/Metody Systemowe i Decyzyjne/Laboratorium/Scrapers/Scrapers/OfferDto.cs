namespace Scrapers;

public class OfferDto
{
    public required string Name { get; set; }
    public required double SalaryFrom { get; set; }
    public required double SalaryTo { get; set; }
    public required string ExpLevel { get; set; }
    public required string Category { get; set; }
    public required string JobLanguage { get; set; }
    public required string Location { get; set; }
    public required bool IsRemote { get; set; }
    public required string Technology { get; set; }
    public required string ExternalId { get; set; }

    public required string CompanyName { get; set; }
    public required int OfferPortalId { get; set; }
}