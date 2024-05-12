using System.Data.SqlClient;
using System.Net.Http.Json;

namespace Scrapers;

public class DatabaseService(SqlConnection connection)
{
    private static readonly Dictionary<string, Func<OfferDto, object?>> SqlParametersFuncs = new()
    {
        { "@Name", offer => offer.Name },
        { "@SalaryFrom", offer => offer.SalaryFrom },
        { "@ExperienceLevel", offer => offer.ExpLevel },
        { "@Company", offer => offer.CompanyName },
        { "@OfferPortal", offer => offer.OfferPortalId },
        { "@Category", offer => offer.Category },
        { "@JobLanguage", offer => offer.JobLanguage },
        { "@Location", offer => offer.Location },
        { "@IsRemote", offer => offer.IsRemote },
        { "@Technologies", offer => offer.Technology },
        { "@ExternalId", offer => offer.ExternalId },
        { "@SalaryTo", offer => offer.SalaryTo },
    };

    public void AddOffer(OfferDto offerDto)
    {
        string query =
            @$"INSERT INTO Offers (Name, SalaryFrom, ExpLevel, Company,
            OfferPortalCompanyId, Category, JobLanguage, Location, IsRemote, Technology, ExternalId, SalaryTo) 
            VALUES ({string.Join(", ", SqlParametersFuncs.Keys)})";
        
        var command = new SqlCommand(query, connection);
        foreach ((string key, Func<OfferDto, object?> value) in SqlParametersFuncs)
        {
            command.Parameters.AddWithValue(key, value(offerDto) ?? DBNull.Value);
        }

        try
        {
            command.ExecuteNonQuery();
        }
        catch (SqlException ex)
        {
            
        }
    }
}