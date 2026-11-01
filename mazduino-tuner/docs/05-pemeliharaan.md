# 05. Maintenance

## When rusEFI / Mazduino adds or changes pages

Nothing breaks. New pages automatically appear in **Expert**. Workflow:

1. Update the branch: `git fetch origin && git rebase origin/master` (or merge).
2. Regenerate: `mazduino-tuner/tools/gen_all_from_gh_pages.sh`.
3. Review the diff of `generated/*/*.tuner-menu.md`. New pages show up in the `## Expert` section.
4. If a page has a MaxxECU equivalent, move it to the right menu in
   `menu/mazduino-tuner-menu.ini`, regenerate, then commit the layout and `generated/`.

If a page ID is renamed upstream, the old ID appears in the "Layout IDs not present on this board" list
for **all** boards, and the page with the new ID goes into Expert. Fix the ID in the layout.

## Checklist for layout changes

- [ ] Short labels, MaxxECU style, in English (consistent with firmware help).
- [ ] No conditions written unless an override is really needed.
- [ ] Generator passes for all boards (`gen_all_from_gh_pages.sh` exits 0).
- [ ] `generated/` is committed too.
- [ ] When adding/moving a top-level menu, update the table in `02-struktur-menu.md`.

## Commit convention

```
mazduino-tuner: <summary>

examples:
mazduino-tuner: move misfire detection from Expert to Limits
mazduino-tuner: regenerate menus for nightly 2026-11-05
```

## References

- MaxxECU MTune 1.161: the full menu tree and its mapping are in the research project
  `Documents/Mazduino-Tuner` (`docs/02-mtune-settings-menu.md`, `docs/05-menu-mapping.md`).
- TunerStudio `[Menu]` syntax: the `[Menu]` section of any firmware INI.
