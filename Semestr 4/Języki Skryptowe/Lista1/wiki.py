import wikipedia

article_name = input("Enter the name of the article: ")

print("Summary of entered article: " + wikipedia.page(article_name).summary)
print("URL of entered article: " + wikipedia.page(article_name).url)