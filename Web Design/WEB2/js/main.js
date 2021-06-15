import model from "./model.js";
import view from "./view.js";
import controller from "./controller.js";

const Model = new model();
const View = new view(Model);

const Controller = new controller(Model, View);
