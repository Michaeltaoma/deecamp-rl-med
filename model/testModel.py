import requests

files = {'data': open('sample_text.txt', 'rb')}
response = requests.post('http://localhost:8080/predictions/morphine', files=files)
data = response.content

