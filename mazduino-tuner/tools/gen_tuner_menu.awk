# gen_tuner_menu.awk - rebuild the [Menu] of a rusEFI TunerStudio INI according to the Mazduino Tuner layout.
#
# Called by gen_tuner_menu.sh:
#   awk -f gen_tuner_menu.awk -v MENU_OUT=.. -v JSON_OUT=.. -v MD_OUT=.. -v BOARD=.. firmware.ini layout.ini
#
# Pass 1 (firmware.ini): collect dialog/table/curve titles + original [Menu] items.
# Pass 2 (layout.ini)  : read the Mazduino Tuner layout.
# END                  : build the new menu, automatic Expert menu, JSON & Markdown.

BEGIN {
	nOrig = 0; nLay = 0; nWarn = 0; nErr = 0
	fileNo = 0
}

FNR == 1 { fileNo++ }

# ---------------------------------------------------------------- helpers ---
function trim(s) { sub(/^[ \t\r]+/, "", s); sub(/[ \t\r]+$/, "", s); return s }

# strip ';' comments that are not inside quotes
function stripComment(s,    i, c, q, out) {
	q = 0; out = ""
	for (i = 1; i <= length(s); i++) {
		c = substr(s, i, 1)
		if (c == "\"") q = !q
		else if (c == ";" && !q) break
		out = out c
	}
	return out
}

# split item value: <id>[,] ["label"] [rest]  -> P_ID, P_LABEL, P_HASLABEL, P_REST
function parseItemValue(v,    m) {
	v = trim(v)
	P_ID = ""; P_LABEL = ""; P_HASLABEL = 0; P_REST = ""
	if (match(v, /^[A-Za-z0-9_]+/)) {
		P_ID = substr(v, 1, RLENGTH)
		v = trim(substr(v, RLENGTH + 1))
		sub(/^,/, "", v); v = trim(v)
	}
	if (substr(v, 1, 1) == "\"") {
		m = index(substr(v, 2), "\"")
		P_LABEL = substr(v, 2, m - 1); P_HASLABEL = 1
		v = trim(substr(v, m + 2))
	}
	P_REST = trim(v)
	sub(/^,[ \t]*/, "", P_REST)
	P_REST = trim(P_REST)
}

# split menu/groupMenu value: "label" [rest]
function parseTitleValue(v,    m) {
	v = trim(v); P_LABEL = ""; P_REST = ""
	if (substr(v, 1, 1) == "\"") {
		m = index(substr(v, 2), "\"")
		P_LABEL = substr(v, 2, m - 1)
		v = trim(substr(v, m + 2))
	}
	sub(/^,[ \t]*/, "", v); P_REST = trim(v)
}

# remaining condition -> R_PAGE, R_ENABLE, R_VISIBLE
function parseRest(r,    s, e, n) {
	R_PAGE = ""; R_ENABLE = ""; R_VISIBLE = ""
	r = trim(r)
	if (match(r, /^[0-9]+/)) { R_PAGE = substr(r, 1, RLENGTH); r = trim(substr(r, RLENGTH + 1)); sub(/^,/, "", r); r = trim(r) }
	n = 0
	while (substr(r, 1, 1) == "{") {
		e = index(r, "}")
		if (e == 0) break
		s = trim(substr(r, 2, e - 2))
		if (n == 0) R_ENABLE = s; else R_VISIBLE = s
		n++
		r = trim(substr(r, e + 1)); sub(/^,/, "", r); r = trim(r)
	}
}

function jsonEsc(s) { gsub(/\\/, "\\\\", s); gsub(/"/, "\\\"", s); gsub(/\t/, " ", s); return s }
function mdEsc(s) { gsub(/\|/, "\\|", s); return s }
function stripAmp(s) { gsub(/&/, "", s); return s }

function warn(msg) { WARN[++nWarn] = msg }
function err(msg) { ERRS[++nErr] = msg }

# ------------------------------------------------- pass 1: firmware INI ---
fileNo == 1 {
	line = $0
	if (line ~ /^[ \t]*\[[A-Za-z]+\]/) {
		sec = line; gsub(/^[ \t]*\[|\].*$/, "", sec)
		next
	}
	if (sec == "UserDefined" && match(line, /^[ \t]*dialog[ \t]*=[ \t]*[A-Za-z0-9_]+[ \t]*,[ \t]*"[^"]*"/)) {
		v = line; sub(/^[ \t]*dialog[ \t]*=[ \t]*/, "", v)
		id = v; sub(/[ \t]*,.*/, "", id)
		t = v; sub(/^[^"]*"/, "", t); sub(/".*/, "", t)
		KIND[id] = "dialog"; TITLE[id] = t
		next
	}
	if (sec == "TableEditor" && match(line, /^[ \t]*table[ \t]*=/)) {
		v = line; sub(/^[ \t]*table[ \t]*=[ \t]*/, "", v)
		split(v, a, /[ \t]*,[ \t]*/)
		t = v; sub(/^[^"]*"/, "", t); sub(/".*/, "", t)
		KIND[a[1]] = "table"; TITLE[a[1]] = t
		if (a[2] != "") { KIND[a[2]] = "table3d"; TITLE[a[2]] = t }
		next
	}
	if (sec == "CurveEditor" && match(line, /^[ \t]*curve[ \t]*=/)) {
		v = line; sub(/^[ \t]*curve[ \t]*=[ \t]*/, "", v)
		id = v; sub(/[ \t]*,.*/, "", id)
		t = v; sub(/^[^"]*"/, "", t); sub(/".*/, "", t)
		KIND[id] = "curve"; TITLE[id] = t
		next
	}
	if (sec == "MegaTune" || sec == "TunerStudio" || sec == "Constants") {
		if (SIGNATURE == "" && line ~ /^[ \t]*signature[ \t]*=/) {
			s = line; sub(/^[^"]*"/, "", s); sub(/".*/, "", s); SIGNATURE = s
		}
	}
	if (sec != "Menu") next

	line = trim(stripComment(line))
	if (line == "" || substr(line, 1, 1) == "#") next
	if (line ~ /^menuDialog[ \t]*=/) { MENU_DIALOG = line; next }
	if (match(line, /^(menu|groupMenu|subMenu|groupChildMenu)[ \t]*=/)) {
		key = line; sub(/[ \t]*=.*/, "", key)
		val = line; sub(/^[^=]*=/, "", val)
		if (key == "menu") { parseTitleValue(val); oMenu = stripAmp(P_LABEL); oGroup = ""; next }
		if (key == "groupMenu") { parseTitleValue(val); oGroup = P_LABEL; next }
		parseItemValue(val)
		if (P_ID == "" || P_ID == "std_separator") next
		nOrig++
		O_ID[nOrig] = P_ID; O_LABEL[nOrig] = P_LABEL; O_REST[nOrig] = P_REST
		O_MENU[nOrig] = oMenu
		O_GROUP[nOrig] = (key == "groupChildMenu") ? oGroup : ""
		if (!(P_ID in FIRST)) FIRST[P_ID] = nOrig
	}
	next
}

# ------------------------------------------------------ pass 2: layout ---
fileNo == 2 {
	line = trim(stripComment($0))
	if (line == "") next
	if (!match(line, /^(menu|groupMenu|subMenu|groupChildMenu|include)[ \t]*=/)) {
		err("layout line " FNR ": not recognized: " line); next
	}
	key = line; sub(/[ \t]*=.*/, "", key)
	val = line; sub(/^[^=]*=/, "", val)
	nLay++
	L_KEY[nLay] = key; L_LINE[nLay] = FNR
	if (key == "menu" || key == "groupMenu") { parseTitleValue(val); L_LABEL[nLay] = P_LABEL; L_REST[nLay] = P_REST; next }
	if (key == "include") { L_ID[nLay] = trim(val); next }
	parseItemValue(val)
	L_ID[nLay] = P_ID; L_LABEL[nLay] = P_LABEL; L_HASLABEL[nLay] = P_HASLABEL; L_REST[nLay] = P_REST
	if (P_ID != "std_separator") {
		if (P_ID in LAYUSED) err("layout line " FNR ": ID '" P_ID "' already used on line " LAYUSED[P_ID])
		else LAYUSED[P_ID] = FNR
	}
	next
}

# -------------------------------------------------------------- output ---
# output entries: E_T = menu|group|item|child|sep
function addEntry(t, id, label, rest, origin) {
	nE++; E_T[nE] = t; E_ID[nE] = id; E_LABEL[nE] = label; E_REST[nE] = rest; E_ORIGIN[nE] = origin
}

function resolveLabel(id, given, hasGiven) {
	if (hasGiven && given != "") return given
	if (O_LABEL[FIRST[id]] != "") return O_LABEL[FIRST[id]]
	if (TITLE[id] != "") return TITLE[id]
	return id
}

function expandUnplaced(    i, id, lastMenu, label, done) {
	lastMenu = "\001"
	for (i = 1; i <= nOrig; i++) {
		id = O_ID[i]
		if ((id in PLACED) || (id in EXPERT_DONE)) continue
		EXPERT_DONE[id] = 1
		if (O_MENU[i] != lastMenu) { addEntry("group", "", O_MENU[i], "", "expert"); lastMenu = O_MENU[i] }
		label = O_LABEL[i]; if (label == "") label = (TITLE[id] != "" ? TITLE[id] : id)
		if (O_GROUP[i] != "") label = O_GROUP[i] " - " label
		addEntry("child", id, label, O_REST[i], "expert:" O_MENU[i])
		nExpert++
	}
}

END {
	if (nOrig == 0) { print "ERROR: no [Menu] items in firmware INI" > "/dev/stderr"; exit 2 }

	# mark layout IDs present in the INI
	for (i = 1; i <= nLay; i++) {
		id = L_ID[i]
		if ((L_KEY[i] == "subMenu" || L_KEY[i] == "groupChildMenu") && id != "std_separator") {
			if (id in FIRST) PLACED[id] = 1
			else { nSkipped++; SKIPLIST = SKIPLIST (SKIPLIST == "" ? "" : ", ") "`" id "`" }
		}
	}

	# build entries
	nE = 0; inGroup = 0; nPlaced = 0; nExpert = 0
	for (i = 1; i <= nLay; i++) {
		k = L_KEY[i]; id = L_ID[i]
		if (k == "menu") { addEntry("menu", "", L_LABEL[i], L_REST[i], "layout"); inGroup = 0; continue }
		if (k == "groupMenu") { addEntry("group", "", L_LABEL[i], L_REST[i], "layout"); inGroup = 1; continue }
		if (k == "include") {
			if (id == "unplaced") expandUnplaced()
			else err("layout line " L_LINE[i] ": unknown include: " id)
			continue
		}
		if (id == "std_separator") { addEntry("sep", "", "", "", "layout"); inGroup = 0; continue }
		if (!(id in FIRST)) continue
		if (k == "groupChildMenu" && !inGroup) err("layout line " L_LINE[i] ": groupChildMenu '" id "' without groupMenu")
		if (k == "subMenu") inGroup = 0
		rest = (L_REST[i] != "") ? L_REST[i] : O_REST[FIRST[id]]
		addEntry(k == "subMenu" ? "item" : "child", id, resolveLabel(id, L_LABEL[i], L_HASLABEL[i]), rest, "layout")
		nPlaced++
	}

	# clean up: empty groups, empty menus, redundant separators
	for (i = 1; i <= nE; i++) KEEP[i] = 1
	for (i = 1; i <= nE; i++) if (E_T[i] == "group") {
		c = 0
		for (j = i + 1; j <= nE && E_T[j] == "child"; j++) c++
		if (c == 0) KEEP[i] = 0
	}
	for (i = 1; i <= nE; i++) if (E_T[i] == "menu") {
		c = 0
		for (j = i + 1; j <= nE && E_T[j] != "menu"; j++) if (KEEP[j] && (E_T[j] == "item" || E_T[j] == "child")) c++
		if (c == 0) { KEEP[i] = 0; for (j = i + 1; j <= nE && E_T[j] != "menu"; j++) KEEP[j] = 0 }
	}
	prev = "menu"
	for (i = 1; i <= nE; i++) {
		if (!KEEP[i]) continue
		if (E_T[i] == "sep") {
			if (prev == "menu" || prev == "sep") { KEEP[i] = 0; continue }
			nxt = ""
			for (j = i + 1; j <= nE; j++) if (KEEP[j]) { nxt = E_T[j]; break }
			if (nxt == "" || nxt == "menu" || nxt == "sep") { KEEP[i] = 0; continue }
		}
		prev = E_T[i]
	}

	# ---- new [Menu] (TunerStudio format) ----
	print "[Menu]" > MENU_OUT
	print "; Generated by mazduino-tuner/tools/gen_tuner_menu.sh - DO NOT EDIT MANUALLY." > MENU_OUT
	print "; Layout: mazduino-tuner/menu/mazduino-tuner-menu.ini" > MENU_OUT
	print (MENU_DIALOG != "" ? MENU_DIALOG : "menuDialog = main") > MENU_OUT
	for (i = 1; i <= nE; i++) {
		if (!KEEP[i]) continue
		t = E_T[i]; r = (E_REST[i] != "") ? ", " E_REST[i] : ""
		if (t == "menu")  { printf "\n\tmenu = \"%s\"%s\n", E_LABEL[i], r > MENU_OUT; continue }
		if (t == "group") { printf "\t\tgroupMenu = \"%s\"%s\n", E_LABEL[i], r > MENU_OUT; continue }
		if (t == "sep")   { print "\t\tsubMenu = std_separator" > MENU_OUT; continue }
		if (t == "item")  { printf "\t\tsubMenu = %s, \"%s\"%s\n", E_ID[i], E_LABEL[i], r > MENU_OUT; continue }
		if (t == "child") { printf "\t\t\tgroupChildMenu = %s, \"%s\"%s\n", E_ID[i], E_LABEL[i], r > MENU_OUT; continue }
	}
	print "" > MENU_OUT
	close(MENU_OUT)

	# ---- JSON ----
	printf "{\n  \"generator\": \"mazduino-tuner/tools/gen_tuner_menu.sh\",\n  \"board\": \"%s\",\n  \"signature\": \"%s\",\n", jsonEsc(BOARD), jsonEsc(SIGNATURE) > JSON_OUT
	printf "  \"stats\": { \"iniItems\": %d, \"placed\": %d, \"expert\": %d, \"skippedNotOnBoard\": %d },\n  \"menus\": [", nOrig, nPlaced, nExpert, nSkipped > JSON_OUT
	firstMenu = 1; openItems = 0; openGroup = 0
	for (i = 1; i <= nE; i++) {
		if (!KEEP[i]) continue
		t = E_T[i]
		if (t != "child" && openGroup) { printf "\n      ]}" > JSON_OUT; openGroup = 0 }
		if (t == "menu") {
			if (!firstMenu) printf "\n    ]}," > JSON_OUT
			parseRest(E_REST[i])
			printf "\n    {\"title\": \"%s\", \"visible\": \"%s\", \"items\": [", jsonEsc(E_LABEL[i]), jsonEsc(R_VISIBLE != "" ? R_VISIBLE : R_ENABLE) > JSON_OUT
			firstMenu = 0; firstItem = 1
			continue
		}
		sepc = firstItem ? "" : ","; firstItem = 0
		if (t == "sep") { printf "%s\n      {\"type\": \"separator\"}", sepc > JSON_OUT; continue }
		if (t == "group") {
			parseRest(E_REST[i])
			printf "%s\n      {\"type\": \"group\", \"title\": \"%s\", \"visible\": \"%s\", \"items\": [", sepc, jsonEsc(E_LABEL[i]), jsonEsc(R_VISIBLE != "" ? R_VISIBLE : R_ENABLE) > JSON_OUT
			openGroup = 1; firstChild = 1; firstItem = 0
			continue
		}
		parseRest(E_REST[i])
		k = (E_ID[i] in KIND) ? KIND[E_ID[i]] : "other"
		obj = sprintf("{\"type\": \"page\", \"id\": \"%s\", \"label\": \"%s\", \"kind\": \"%s\", \"enable\": \"%s\", \"visible\": \"%s\", \"origin\": \"%s\"}", \
			jsonEsc(E_ID[i]), jsonEsc(E_LABEL[i]), k, jsonEsc(R_ENABLE), jsonEsc(R_VISIBLE), jsonEsc(E_ORIGIN[i]))
		if (t == "child" && openGroup) {
			printf "%s\n        %s", (firstChild ? "" : ","), obj > JSON_OUT; firstChild = 0
		} else {
			printf "%s\n      %s", sepc, obj > JSON_OUT
		}
	}
	if (openGroup) printf "\n      ]}" > JSON_OUT
	if (!firstMenu) printf "\n    ]}" > JSON_OUT
	printf "\n  ]\n}\n" > JSON_OUT
	close(JSON_OUT)

	# ---- Markdown ----
	print "# Mazduino Tuner menu - " BOARD > MD_OUT
	print "" > MD_OUT
	print "> Generated by `mazduino-tuner/tools/gen_tuner_menu.sh` - do not edit manually." > MD_OUT
	print "> Signature: `" SIGNATURE "`" > MD_OUT
	print "" > MD_OUT
	print "| Statistic | Count |" > MD_OUT
	print "|---|---:|" > MD_OUT
	print "| Menu items in firmware INI | " nOrig " |" > MD_OUT
	print "| Placed in MaxxECU-style menus | " nPlaced " |" > MD_OUT
	print "| Automatically added to Expert menu | " nExpert " |" > MD_OUT
	print "| Layout IDs not present on this board (skipped) | " nSkipped " |" > MD_OUT
	print "" > MD_OUT
	for (i = 1; i <= nE; i++) {
		if (!KEEP[i]) continue
		t = E_T[i]
		k = (E_ID[i] in KIND) ? KIND[E_ID[i]] : "other"
		if (t == "menu")  { print "\n## " E_LABEL[i] "\n" > MD_OUT; continue }
		if (t == "group") { print "- **" mdEsc(E_LABEL[i]) "**" > MD_OUT; continue }
		if (t == "sep")   { print "- ---" > MD_OUT; continue }
		ind = (t == "child") ? "  " : ""
		print ind "- " mdEsc(E_LABEL[i]) " - _" k "_ `" E_ID[i] "`" > MD_OUT
	}
	if (nSkipped > 0) {
		print "\n## Layout IDs not present on this board\n" > MD_OUT
		print SKIPLIST > MD_OUT
	}
	close(MD_OUT)

	for (i = 1; i <= nWarn; i++) print "WARN: " WARN[i] > "/dev/stderr"
	for (i = 1; i <= nErr; i++) print "ERROR: " ERRS[i] > "/dev/stderr"
	printf "%s: %d INI items -> %d placed, %d Expert, %d skipped\n", BOARD, nOrig, nPlaced, nExpert, nSkipped > "/dev/stderr"
	if (nErr > 0) exit 1
}
