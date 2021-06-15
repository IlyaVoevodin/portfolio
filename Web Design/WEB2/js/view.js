export default class view {
  constructor(model) {
    this.model = model;
    document.querySelector("#new").addEventListener("click", () => {
      const title = document.querySelector("#title").value;
      const text = document.querySelector("#text").value;
      if (title.trim() && text.trim()) {
        this.model.createPost(title, text);
      } else {
        alert("empty inputs");
      }
    });
    document.querySelector("#app").addEventListener("click", (e) => {
      if (e.target.classList.contains("delete")) {
        this.model.removePost(e.target.parentNode.id);
      }
    });
  }
  renderItem(i) {
    return `
      <article class="blog-post" id="${this.model.posts[i].id}">
      <h2 class="blog-post-title">${this.model.posts[i].title}</h2>
      <p class="blog-post-meta">January 1, 2014 by <a href="#">${this.model.posts[i].author}</a></p>
      <hr>
      <p>${this.model.posts[i].text}</p>

      <button class="btn btn-outline-warning delete">Delete</button>
    </article><!-- /.blog-post -->`;
  }

  toHtml() {
    const items = this.model.posts
      .map((post, i) => {
        return this.renderItem(i);
      })
      .join("");
    document.querySelector("#app").innerHTML = items;
  }
}
