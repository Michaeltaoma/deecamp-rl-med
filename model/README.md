## Package model into .mar
<code>torch-model-archiver --model-name morphine  --version 1.0 --model-file ddqn_model.py --serialized-file saved/naive_ddqn_state_dict.pt  --handler ddqn_handler.py --extra-files saved/naive_ddqn_state_dict.pt</code>

## Serve the model
<code>torchserve --start --model-store model_store/  --models morphine=morphine.mar</code>

## Inference
### With cmd
<code>curl http://127.0.0.1:8080/predictions/morphine -T sample_text.txt</code>

### With script

```python
import requests
files = {'data': open('sample_text.txt', 'rb')}
response = requests.post('http://localhost:8080/predictions/morphine', files=files)
data = response.content
```
