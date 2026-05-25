from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
import time
import os

# Percorso assoluto al file HTML
html_path = os.path.abspath("social_preview.html")
# Imposta la directory di lavoro dove si trova il logo
os.chdir(os.path.dirname(html_path))

chrome_options = Options()
chrome_options.add_argument("--headless")
chrome_options.add_argument("--no-sandbox")
chrome_options.add_argument("--disable-dev-shm-usage")
chrome_options.add_argument("--window-size=1280,640")
chrome_options.add_argument("--force-device-scale-factor=2")  # retina

driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=chrome_options)
driver.get(f"file://{html_path}")
time.sleep(1)  # attesa rendering
driver.save_screenshot("docs/demo/social_preview.png")
driver.quit()
print("Screenshot saved to docs/demo/social_preview.png")
