# Noru WM theme example

This folder is an example **Emerald-like** window-manager theme for Mir/Lomiri decorations, using the new WM theme layout.

## WM config + theme layout

Noru now reads the active WM theme from `config.toml`:

- User config: `~/.config/noru/wm/config.toml`
- System config: `/usr/share/noru/wm/config.toml`

`config.toml` must define:

```toml
theme = "<theme name>"
```

Theme assets are loaded from:

- User theme dir: `~/.config/noru/wm/<theme name>/`
- System theme dir: `/usr/share/noru/wm/<theme name>/`

Each theme directory should contain an `index.toml` file that maps asset names to files.

## Supported `index.toml` keys

- `close`
- `close_hover`
- `minimize`
- `maximize`
- `restore`
- `titlebar` (PNG)
- `titlebar_svg` (SVG)

## Example files in this folder

- `config.toml`
- `emerald/index.toml`
- `emerald/titlebar.svg`
- `emerald/close.svg`
- `emerald/close_hover.svg`
- `emerald/minimize.svg`
- `emerald/maximize.svg`
- `emerald/restore.svg`

## Quick test

```bash
mkdir -p ~/.config/noru/wm/emerald
cp examples/wm-theme/config.toml ~/.config/noru/wm/config.toml
cp examples/wm-theme/emerald/* ~/.config/noru/wm/emerald/
```

Then restart Lomiri/Mir session.