# 03. Layout file format (`menu/mazduino-tuner-menu.ini`)

The syntax is a subset of the TunerStudio `[Menu]` section, plus one `include` directive.

## Elements

| Line | Meaning |
|---|---|
| `menu = "Title"` | Top-level menu (level 1, one node in the left tree / menubar) |
| `subMenu = <id>[, "Label"][, condition]` | Page directly under the menu |
| `groupMenu = "Title"` | Group inside the menu (level 2) |
| `groupChildMenu = <id>[, "Label"][, condition]` | Page inside the group (level 3) |
| `subMenu = std_separator` | Separator line |
| `include = unplaced` | Insert all INI pages not yet placed (used in the **Expert** menu) |
| `; comment` | Comment (outside quotes) |

`<id>` is the name of a dialog/table/curve in the firmware INI. Look in `[UserDefined]` (`dialog = id`),
`[TableEditor]` (`table = id`) or `[CurveEditor]` (`curve = id`), or see the ID column in
`generated/<board>/<board>.tuner-menu.md`.

## Conditions

The condition format is the same as TunerStudio: `[page,] {enable}[, {visible}]`.

```ini
subMenu = veTableDialog                          ; label & condition inherited from INI
subMenu = veTableDialog, "Fuel table"            ; new label, condition inherited
subMenu = veTableDialog, "Fuel table", 0, { isInjectionEnabled == 1 }   ; everything overridden
```

Prefer **not writing** conditions so they automatically follow upstream changes.

## Validation rules (the generator fails if violated)

- An `<id>` may appear only once in the layout.
- `groupChildMenu` must come after a `groupMenu` in the same menu.
- Only the elements in the table above are recognized.
- `include` only accepts `unplaced`.

## Automatic behavior

- An `<id>` that does not exist in the board's INI → skipped and listed in the "Layout IDs not present" section of the `.md`.
- Groups without pages, menus without pages, and leading/trailing or consecutive separators → removed.
- Expert items are labeled `"<original group> - <label>"` when they come from inside a TunerStudio group.
- A dialog that appears twice in the original INI is added to Expert only once.

## Limitations

- TunerStudio supports only one level of groups. The maximum structure is therefore
  menu → group → page, the same as the 3 levels in MaxxECU.
- Conditions on the original `groupMenu` are not carried into Expert. This is safe because every page
  inside it already has its own condition.
