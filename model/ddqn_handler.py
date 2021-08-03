import ast
import logging
import numpy as np
import torch
import os
from ddqn_model import QNetwork
from torch.nn.functional import Tensor
from ts.torch_handler.base_handler import BaseHandler

logger = logging.getLogger(__name__)


class MorphineDuelDoubleQNetwork(BaseHandler):

    def __init__(self):
        super().__init__()
        self.ddqn_model = None
        self.mapping = None
        self.device = None
        self.initialized = False
        self.metrics = None

    def initialize(self, context):
        properties = context.system_properties
        model_dir = properties.get("model_dir")
        self.device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

        ddqn_state_dict = torch.load(os.path.join(model_dir, "naive_ddqn_state_dict.pt"))
        self.ddqn_model = QNetwork()
        self.ddqn_model.load_state_dict(ddqn_state_dict)
        self.ddqn_model.to(self.device)
        self.ddqn_model.eval()

        logger.debug("DDQN model file loaded successfully")
        self.initialized = True

    def preprocess(self, data) -> Tensor:
        text = data[0].get("data")
        if text is None:
            text = data[0].get("body")
        input_text = text.decode('utf-8')

        logger.info("Received decoded text: '%s'", input_text)

        question_context = ast.literal_eval(input_text)
        hr = question_context["hr"]
        rr = question_context["rr"]
        pl = question_context["pl"]

        return self._state_package([float(i) for i in [hr, rr, pl]])

    def inference(self, data, *args, **kwargs):
        with torch.no_grad():
            result = self.ddqn_model.select_action(data)
        return [result]

    def postprocess(self, data):
        return data

    def _state_package(self, state: list) -> Tensor:
        return torch.FloatTensor(np.array(state)).unsqueeze(0).to(self.device)

    def handle(self, data, context):
        try:
            if data is None:
                return None

            data = self.preprocess(data)
            data = self.inference(data)
            data = self.postprocess(data)

            return data
        except Exception as e:
            raise e



