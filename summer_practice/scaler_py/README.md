# Web Scraper

A simple command-line web scraper written in Python for extracting text from HTML elements of a web page.

The project was created as a practical exercise in working with HTTP requests, HTML parsing, command-line arguments, and file processing in Python.

The scraper accepts a URL, downloads the page, parses its HTML structure, extracts text from the specified HTML tag, and optionally saves the result to a text file.

## Features

- Fetching web pages using HTTP requests
- Extraction of text from any specified HTML tag
- Saving extracted data to a text file
- Automatic response encoding detection

## How It Works

The application processes a web page in several steps:

1. The URL is provided as a command-line argument.
2. The program sends an HTTP GET request using the `requests` library.
3. A browser-like `User-Agent` header is used for the request.
4. The received HTML document is parsed using `BeautifulSoup`.
5. The program searches for elements matching the specified HTML tag.
6. Text is extracted from each found element.
7. The extracted data is written to the output file.
8. The program reports the number of extracted elements and the output file name.

By default, the scraper extracts the text from all `<h1>` elements on the page.

## Command-Line Usage

The basic command is:

```bash
python scaler.py https://ru.wikipedia.org --tag p --output result.txt
