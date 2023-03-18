# tmplrun

To me, bash and LLMs have a natural affinity:

1. They're both text-in/text-out.
2. They both deal with lots of unstructured text.
3. And they both make words feel magic.

So recently I've been working with OpenAI's LLM APIs from bash a lot.

When I started working on projects this way, I switched from static, one-off prompts to **prompt templates**.

So, naturally, I've been thinking about the ideal pattern for **prompt templates** in *bash*... 💬🏃

---

Introducing... `tmplrun`: executable templates, perfect for working with LLMs in bash. Here's an example template:

```sh
#!/usr/bin/env tmplrun
Write a poem about $1. The tone should be $tone.
```

After saving the above to `poem.tmpl`, you can apply the template like this in bash:

```sh
$ tone=happy ./poem.tmpl "Open Source Software"
Write a poem about Open Source Software. The tone should be happy.
```
