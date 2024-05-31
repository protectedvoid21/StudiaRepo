namespace Scrapers;

public class PracujResponse
{
    public Props props { get; set; }
    public string page { get; set; }
    public Query query { get; set; }
    public string buildId { get; set; }
    public string assetPrefix { get; set; }
    public RuntimeConfig runtimeConfig { get; set; }
    public bool isFallback { get; set; }
    public bool gssp { get; set; }
    public bool appGip { get; set; }
    public object[] scriptLoader { get; set; }
}

public class Props
{
    public PageProps pageProps { get; set; }
    public bool __N_SSP { get; set; }
}

public class PageProps
{
    public Data data { get; set; }
    public User user { get; set; }
    public string userIdentifier { get; set; }
    public string userAgent { get; set; }
    public string userCookieString { get; set; }
    public UserAgreements userAgreements { get; set; }
    public SearchCriteria searchCriteria { get; set; }
    public BusinessVariables businessVariables { get; set; }
    public string[] acceptedParameters { get; set; }
    public string langCode { get; set; }
    public DehydratedState dehydratedState { get; set; }
}

public class Data
{
    public CounterJobOffers counterJobOffers { get; set; }
    public JobOffers jobOffers { get; set; }
    public int wholePolandSwitchBoxJobOffersCount { get; set; }
    public SeoContent seoContent { get; set; }
    public PositionedJobOffers positionedJobOffers { get; set; }
    public OffersListBoosterJobOffers offersListBoosterJobOffers { get; set; }
    public MultiregionBoosterJobOffers multiregionBoosterJobOffers { get; set; }
    public Dictionaries dictionaries { get; set; }
}

public class CounterJobOffers
{
    public int offersCount { get; set; }
    public int jobCenterOffersCount { get; set; }
}

public class JobOffers
{
    public PracujOffer[] groupedOffers { get; set; }
    public int offersTotalCount { get; set; }
    public int groupedOffersTotalCount { get; set; }
}

public class PracujOffer
{
    public string groupId { get; set; }
    public string jobTitle { get; set; }
    public string companyName { get; set; }
    public string companyProfileAbsoluteUri { get; set; }
    public int companyId { get; set; }
    public string companyLogoUri { get; set; }
    public string lastPublicated { get; set; }
    public string expirationDate { get; set; }
    public string salaryDisplayText { get; set; }
    public string jobDescription { get; set; }
    public bool isSuperOffer { get; set; }
    public bool isFranchise { get; set; }
    public bool isOptionalCv { get; set; }
    public bool isOneClickApply { get; set; }
    public bool isJobiconCompany { get; set; }
    public Offers[] offers { get; set; }
    public string[] positionLevels { get; set; }
    public string[] typesOfContract { get; set; }
    public string[] workSchedules { get; set; }
    public string[] workModes { get; set; }
    public PrimaryAttributes[] primaryAttributes { get; set; }
    public object commonOfferId { get; set; }
    public int searchEngineRelevancyScore { get; set; }
    public string mobileBannerUri { get; set; }
    public string desktopBannerUri { get; set; }
    public object[] appliedProducts { get; set; }
}

public class Offers
{
    public int partitionId { get; set; }
    public string offerAbsoluteUri { get; set; }
    public string displayWorkplace { get; set; }
    public bool isWholePoland { get; set; }
    public object[] appliedProducts { get; set; }
}

public class PrimaryAttributes
{
    public string code { get; set; }
    public Label label { get; set; }
    public Model model { get; set; }
}

public class Label
{
    public string text { get; set; }
    public string pracujPlText { get; set; }
    public string primaryTargetSiteText { get; set; }
}

public class Model
{
    public string modelType { get; set; }
    public bool flag { get; set; }
    public int? number { get; set; }
}

public class SeoContent
{
    public string title { get; set; }
    public string description { get; set; }
    public bool shouldBeIndexed { get; set; }
    public string canonicalUrl { get; set; }
    public string seoArticle { get; set; }
    public object[] faqSeoArticle { get; set; }
    public Breadcrumbs breadcrumbs { get; set; }
    public string headerTitle { get; set; }
    public string headerSubtitle { get; set; }
}

public class Breadcrumbs
{
    public Items[] items { get; set; }
}

public class Items
{
    public string label { get; set; }
    public string absoluteUrl { get; set; }
    public Children[] children { get; set; }
}

public class Children
{
    public string label { get; set; }
    public string absoluteUrl { get; set; }
}

public class PositionedJobOffers
{
    public object[] groupedOffers { get; set; }
    public int groupedOffersTotalCount { get; set; }
    public int offersTotalCount { get; set; }
}

public class OffersListBoosterJobOffers
{
    public object[] groupedOffers { get; set; }
    public int groupedOffersTotalCount { get; set; }
    public int offersTotalCount { get; set; }
}

public class MultiregionBoosterJobOffers
{
    public object[] groupedOffers { get; set; }
    public int groupedOffersTotalCount { get; set; }
    public int offersTotalCount { get; set; }
}

public class Dictionaries
{
    public Categories[] categories { get; set; }
    public ContractTypes[] contractTypes { get; set; }
    public PositionLevels[] positionLevels { get; set; }
    public WorkModes[] workModes { get; set; }
    public WorkSchedules[] workSchedules { get; set; }
    public TimeUnits[] timeUnits { get; set; }
    public Periods[] periods { get; set; }
    public object[] locations { get; set; }
    public object[] agglomerations { get; set; }
    public object[] foreignLocations { get; set; }
    public Regions[] regions { get; set; }
    public Countries[] countries { get; set; }
}

public class Categories
{
    public int id { get; set; }
    public string name { get; set; }
    public int? parentId { get; set; }
    public int level { get; set; }
}

public class ContractTypes
{
    public int id { get; set; }
    public string name { get; set; }
}

public class PositionLevels
{
    public int id { get; set; }
    public string name { get; set; }
    public string code { get; set; }
}

public class WorkModes
{
    public string code { get; set; }
    public string name { get; set; }
}

public class WorkSchedules
{
    public int id { get; set; }
    public string name { get; set; }
}

public class TimeUnits
{
    public int id { get; set; }
    public string name { get; set; }
    public string shortForm { get; set; }
    public string longForm { get; set; }
    public string code { get; set; }
}

public class Periods
{
    public string key { get; set; }
    public string value { get; set; }
}

public class Regions
{
    public int id { get; set; }
    public string name { get; set; }
    public string code { get; set; }
}

public class Countries
{
    public int id { get; set; }
    public int countryId { get; set; }
    public string name { get; set; }
}

public class User
{
    public int userId { get; set; }
    public string email { get; set; }
    public string givenName { get; set; }
    public string familyName { get; set; }
    public bool emailVerified { get; set; }
    public bool isConfirmed { get; set; }
    public string hashedEmail { get; set; }
}

public class UserAgreements
{
    public string gpc_ad { get; set; }
    public string gpc_analytic { get; set; }
    public string gpc_audience { get; set; }
    public string gpc_func { get; set; }
    public string gpc_social { get; set; }
    public string gpc_v { get; set; }
}

public class SearchCriteria
{
    public int[] cc { get; set; }
    public int pn { get; set; }
}

public class BusinessVariables
{
    public string LINK_HOMEPAGE { get; set; }
    public string LINK_JOB_OFFERS { get; set; }
    public string LINK_JOB_OFFERS_IT { get; set; }
    public string LINK_JOB_OFFERS_BLUE { get; set; }
    public string LINK_JOB_OFFERS_SALES { get; set; }
    public string LINK_JOB_OFFERS_UA { get; set; }
    public string LINK_JOB_SUPEROFFERS { get; set; }
    public string LINK_FIRST_JOB { get; set; }
    public string LINK_EMPLOYERS { get; set; }
    public string LINK_EMPLOYERS_PROFILES { get; set; }
    public string LINK_CV_CREATOR { get; set; }
    public string LINK_CODEJOBS { get; set; }
    public string LINK_TIPS { get; set; }
    public string LINK_LOGIN { get; set; }
    public string LINK_LOGOUT { get; set; }
    public string LINK_REGISTER { get; set; }
    public string LINK_PROFILE { get; set; }
    public string LINK_ACCOUNT { get; set; }
    public string LINK_SAVED_OFFERS { get; set; }
    public string LINK_RECOMMENDED_OFFERS { get; set; }
    public string LINK_MY_SEND_JOB_REQUESTS { get; set; }
    public string LINK_JOB_ALERTS { get; set; }
    public string LINK_DOCS { get; set; }
    public string LINK_SETTINGS { get; set; }
    public string LINK_SALARIES { get; set; }
    public string LINK_SALARIES_CALCULATOR { get; set; }
    public string LINK_SALARIES_CALCULATORS { get; set; }
    public string LINK_HOURLY_PAYCHECK_CALCULATOR { get; set; }
    public string LINK_JOBICON { get; set; }
    public string LINK_THE_PROTOCOL { get; set; }
    public string LINK_THE_PROTOCOL_BLOG { get; set; }
    public string LINK_FOR_EMPLOYERS { get; set; }
    public string LINK_ADVICE_FOR_EMPLOYERS { get; set; }
    public string LINK_ADD_OFFER { get; set; }
    public string LINK_EMPLOYER_PROFILE { get; set; }
    public string LINK_EMPLOYER_HELP { get; set; }
    public string LINK_HIRE { get; set; }
    public string LINK_RABOTA { get; set; }
    public string LINK_LABOR_OFFICES { get; set; }
    public string LINK_ABOUT { get; set; }
    public string LINK_PRESS { get; set; }
    public string LINK_ADS { get; set; }
    public string LINK_PARTNERS { get; set; }
    public string LINK_OFFERS_ARCHIVE { get; set; }
    public string LINK_HELP { get; set; }
    public string LINK_REGULATIONS { get; set; }
    public string LINK_PRIVACY_POLICY { get; set; }
    public string LINK_PRIVACY_SETTINGS { get; set; }
    public string LINK_COOKIES_POLICY { get; set; }
    public string LINK_COOKIES_PARTNERS { get; set; }
    public string LINK_COOKIES_DATA_COLLECTION_POLICY { get; set; }
    public string LINK_DIGITAL_SERVICES_ACT { get; set; }
    public string LINK_GOOGLE_PLAY_APP { get; set; }
    public string LINK_APPSTORE_APP { get; set; }
    public string LINK_FACEBOOK { get; set; }
    public string LINK_YOUTUBE { get; set; }
    public string LINK_INSTAGRAM { get; set; }
    public string LINK_GRUPA_PRACUJ { get; set; }
    public string LINK_THE_NETWORK { get; set; }
    public string LINK_E_RECRUITER { get; set; }
    public string LINK_E_RECRUITER_BLOG { get; set; }
    public string LINK_SOFT_GARDEN { get; set; }
    public string LINK_ABSENCE { get; set; }
}

public class DehydratedState
{
    public object[] mutations { get; set; }
    public Queries[] queries { get; set; }
}

public class Queries
{
    public State state { get; set; }
    public string[] queryKey { get; set; }
    public string queryHash { get; set; }
}

public class State
{
    public object[] data { get; set; }
    public int dataUpdateCount { get; set; }
    public long dataUpdatedAt { get; set; }
    public object error { get; set; }
    public int errorUpdateCount { get; set; }
    public int errorUpdatedAt { get; set; }
    public int fetchFailureCount { get; set; }
    public object fetchMeta { get; set; }
    public bool isInvalidated { get; set; }
    public string status { get; set; }
    public string fetchStatus { get; set; }
}

public class Query
{
    public string searchCriteria { get; set; }
}

public class RuntimeConfig
{
    public string APP_NAME { get; set; }
    public string APP_VERSION { get; set; }
    public string API_CLIENT_GATEWAY { get; set; }
    public string CDN_ROOT_PATH { get; set; }
    public string CDN_PATH { get; set; }
    public string ENVIRONMENT { get; set; }
    public bool SENTRY_ENABLED { get; set; }
    public string SENTRY_DSN { get; set; }
    public string SENTRY_RELEASE_VERSION { get; set; }
    public string SENTRY_RELEASE_NAME { get; set; }
    public string API_INTERNAL_TRANSLATE { get; set; }
    public string SUPPORTED_BROWSERS { get; set; }
    public string TRACKER_CORE_URL { get; set; }
    public string TRACKER_COOKIE_DOMAIN { get; set; }
    public string TRACKER_COLLECTOR_ENDPOINT { get; set; }
    public bool TRACKER_ENABLED { get; set; }
    public bool GTM_ENABLED { get; set; }
    public string GTM_CONTAINER_ID { get; set; }
    public bool ADS_ENABLED { get; set; }
}

