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
        properties = ctx.system_properties
        model_dir = properties.get("model_dir")
        if not torch.cuda.is_available() or properties.get("gpu_id") is None:
            raise RuntimeError("This model is not supported on CPU machines.")
        self.device = torch.device("cuda:" + str(properties.get("gpu_id")))

        ddqn_state_dict = torch.load(os.path.join(model_dir, "naive_ddqn_state_dict.pt"))
        self.ddqn_model = QNetwork()
        self.ddqn_model.load_state_dict(ddqn_state_dict)
        self.ddqn_model.to(self.device)
        self.ddqn_model.eval()

        logger.debug("DDQN model file loaded successfully")
        self.initialized = True

    def preprocess(self, data) -> Tensor:
        hr = data["hr"]
        rr = data["rr"]
        pl = data["pl"]

        return self._state_package([float(i) for i in [hr, rr, pl]])

    def inference(self, data, *args, **kwargs):
        with torch.no_grad():
            result = self.ddqn_model.select_action(data)
            return result

    def postprocess(self, data):
        return int(data)

    def _state_package(self, state: list) -> Tensor:
        return torch.FloatTensor(np.array(state)).unsqueeze(0).to(self.device)
