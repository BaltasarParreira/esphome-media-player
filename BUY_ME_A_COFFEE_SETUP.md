# Buy Me a Coffee setup

Use this when adding the same Buy Me a Coffee control to similar projects.

## Exact button details

- Link URL: `https://www.buymeacoffee.com/jtenniswood`
- Image URL: `https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png`
- Image alt text: `Buy Me A Coffee`
- Image height: `60`
- Rounded style: `border-radius:999px;`
- Floating web button position: `right:28px;bottom:28px;`

## Docs page button

Add this support block where the docs homepage or README should show the button:

```markdown
## Support This Project

If you find this project useful, consider buying me a coffee to support ongoing development!

<a href="https://www.buymeacoffee.com/jtenniswood" target="_blank">
  <img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" height="60" style="border-radius:999px;" />
</a>
```

For README files, omit `target="_blank"` if the project style does not already use it:

```html
<a href="https://www.buymeacoffee.com/jtenniswood">
  <img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" height="60" style="border-radius:999px;" />
</a>
```

## VitePress docs floating widget

If the project uses VitePress, add this to `docs/.vitepress/config.js` inside the exported config:

```js
head: [
  [
    'script',
    {
      'data-name': 'BMC-Widget',
      'data-cfasync': 'false',
      src: 'https://cdnjs.buymeacoffee.com/1.0.0/widget.prod.min.js',
      'data-id': 'jtenniswood',
      'data-description': 'Support me on Buy me a coffee!',
      'data-message': '',
      'data-color': '#FFDD00',
      'data-position': 'Right',
      'data-x_margin': '28',
      'data-y_margin': '28',
    },
  ],
],
```

If `head` already exists, add the script entry to the existing array instead of replacing the rest of the config.

## Webserver floating button

Add a fixed-position support link to the webserver JavaScript:

```js
function addSupportButton() {
  if (document.querySelector(".sp-support-btn")) return;
  var link = document.createElement("a");
  link.className = "sp-support-btn";
  link.href = "https://www.buymeacoffee.com/jtenniswood";
  link.target = "_blank";
  link.rel = "noopener";
  link.innerHTML = '<img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" height="60" style="border-radius:999px;">';
  document.body.appendChild(link);
}
```

Call `addSupportButton()` after the webserver app has created its main page container.

Add this CSS:

```css
.sp-support-btn{position:fixed;right:28px;bottom:28px;z-index:150;display:inline-block;line-height:0}
.sp-support-btn img{height:60px;display:block;border-radius:999px}
```

## Checks

For this project, run:

```sh
npm run webserver:build
npm run check:generated
npm run docs:build
node --check docs/webserver/src/app.template.js
node --check docs/public/webserver/app.js
```

Other similar projects may have different build commands, but the important checks are:

- Rebuild any generated webserver bundle.
- Run the generated-file check if the project has one.
- Build the docs site if the docs config changed.
- Run a JavaScript syntax check on edited/generated webserver scripts.
