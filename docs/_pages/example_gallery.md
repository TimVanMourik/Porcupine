---
layout: archive
title: "Gallery"
permalink: /examples/
author_profile: false
---

Here you find a collection of .pork files. We'd love to include more examples,
so if you feel like contributing your pipeline to our piggy bank,
check our instructions to contribute to our example gallery <span style="color:#52adc8">**[here](/Porcupine/examples/contributing).**</span>

<div class="grid__wrapper">
  {% for post in site.examples %}
    {% include archive-single.html type="grid" %}
  {% endfor %}
</div>
