namespace Scrapers;

public record NflResponse(
    CriteriaSearch CriteriaSearch,
    Posting[] Postings,
    int TotalCount,
    int TotalPages,
    int ExactMatchesPages,
    string RawSearch,
    bool LocationCriteria,
    int Divs,
    object[] AdditionalSearch,
    SalaryMatchBlock SalaryMatchBlock,
    OverridenSalaryFilter OverridenSalaryFilter,
    int NonSmOffersCount,
    bool SmOffersPresents
);

public record CriteriaSearch(
    object[] Country,
    object[] WithSalaryMatch,
    object[] City,
    object[] More,
    object[] Employment,
    object[] Requirement,
    object[] Salary,
    object[] JobPosition,
    object[] Province,
    object[] Company,
    object[] Id,
    string[] Category,
    object[] Keyword,
    object[] JobLanguage,
    object[] Seniority
);

public record Posting(
    string Id,
    string Name,
    Location Location,
    long Posted,
    string Title,
    string Technology,
    Logo Logo,
    string Category,
    string[] Seniority,
    string Url,
    string[] Regions,
    bool FullyRemote,
    Salary Salary,
    string[] Flavors,
    bool TopInSearch,
    bool Highlighted,
    bool Help4Ua,
    string Reference,
    bool SearchBoost,
    bool OnlineInterviewAvailable,
    Tiles Tiles,
    long Renewed
);

public record Location(
    Places[] Places,
    bool FullyRemote,
    bool CovidTimeRemotely
);

public record Places(
    Country Country,
    string City,
    string Street,
    string PostalCode,
    GeoLocation GeoLocation,
    string Url,
    string Province,
    bool ProvinceOnly
);

public record Country(
    string Code,
    string Name
);

public record GeoLocation(
    double Latitude,
    double Longitude
);

public record Logo(
    string Original,
    string JobsDetails,
    string JobsListing,
    string JobsDetails2x,
    string JobsListing2x,
    string CompaniesDetails,
    string CompaniesListing,
    string CompaniesDetails2x,
    string CompaniesListing2x,
    string JobsDetailsWebp,
    string JobsListingWebp,
    string JobsDetails2xWebp,
    string JobsListing2xWebp,
    string OriginalPixelImage,
    string CompaniesDetailsWebp,
    string CompaniesListingWebp,
    string CompaniesDetails2xWebp,
    string CompaniesListing2xWebp
);

public record Salary(
    double From,
    double To,
    string Type,
    string Currency,
    string DisclosedAt
);

public record Tiles(
    Values[] Values
);

public record Values(
    string Value,
    string Type
);

public record SalaryMatchBlock(
    object[] Offers,
    int TotalCount,
    int Divs
);

public record OverridenSalaryFilter(

);
