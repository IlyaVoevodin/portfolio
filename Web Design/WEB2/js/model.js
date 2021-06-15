export default class model {
  constructor() {
    this.posts = [];
    this.onChangeCallback = null;
    return this.onModelChange();
  }

  removePost(id) {
    const postIdx = this.posts.findIndex((item) => +item.id === +id);

    this.posts.splice(postIdx, 1);
    this.onChangeCallback = this.onChangeCallback;
  }

  createPost(title, text, author = "admin") {
    const newPost = {
      id: Math.round(Math.random() * 100000).toString(),
      comments: [],
      title,
      text,
      author,
    };
    this.posts.push(newPost);
    this.onChangeCallback = this.onChangeCallback;
  }

  createComment(text, author = "admin") {
    let newComment = { author: author, text: text };
    this.posts[info.id].comments.push(newComment);
  }

  setOnChangeCallback(func) {
    this.onChangeCallback = func;
  }
  onModelChange() {
    let handler = {
      set: (obj, prop, val) => {
        obj[prop] = val;
        if (this.onChangeCallback) this.onChangeCallback();
        return true;
      },
    };
    return new Proxy(this, handler);
  }
}
