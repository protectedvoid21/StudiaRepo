namespace Scrapers;

public record NflRequest(
    int PageTo,
    int PageSize,
    bool WithSalaryMatch);