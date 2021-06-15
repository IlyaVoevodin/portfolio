export default class controller {
  constructor(model, view) {
    this.model = model;
    this.view = view;
    this.model.setOnChangeCallback(() => this.onChangeCallback());
  }

  onChangeCallback() {
    this.view.toHtml();
  }
}
