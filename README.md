# tmplrun

To me, bash and LLMs have a natural affinity:

1. They're both text-in/text-out.
2. They both work great on unstructured text.
3. And they both make words feel magic.

Recently, I've been working with OpenAI's LLM APIs from bash a lot. When I
started working on projects this way, I quickly switched from static, one-off
prompts to **prompt templates**.

Naturally, I've been thinking about the ideal pattern for **prompt templates** in *bash*... 💬🏃

## Introduction

tmplrun turns templates into executables. It couldn't be easier to use. Here's
an example template:

```sh
#!/usr/bin/env tmplrun
Write a story about $1 and $2 in the style of $style.
```

The magic shebang in the first line turns this into an executable template. If
you save the above to `story.tmpl`, you can apply the template like this in
bash:

```sh
$ style=Hemingway ./story.tmpl Dragons Trains
Write a story about Dragons and Trains in the style of Hemingway.
```

**Note**: Don't forget to make your template executable (`chmod +x story.tmpl`)

## Features

Templates can be parameterized by positional arguments or named arguments, as
seen above. This behavior is inherited from bash.

Because tmplrun templates are effectively bash scripts, they can call each
other. This makes transclusion super simple. Here's an example of an advanced
template:

```sh
Write a story about $1 and $2 in the style of $style, incorporating these
events:

$(./events.tmpl)
```

Implicitly, the `$style` argument would be made available in `events.tmpl` as
well.

## Installation

To get started, install `tmplrun` as a global module using npm:

```sh
$ npm i -g tmplrun
```

Then, just use it in the shebang of template files to turn them into
executables.
