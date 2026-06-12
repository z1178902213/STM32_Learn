import os
import shutil
import chardet

def get_file_encoding(file_path: str) -> str:
    """检测文件真实编码"""
    with open(file_path, "rb") as f:
        raw_data = f.read()
    result = chardet.detect(raw_data)
    enc = result["encoding"]
    if enc is None:
        return "unknown"
    # 统一别名映射
    enc_map = {
        "cp1252": "gbk",
        "gb2312": "gbk",
        "gb18030": "gbk",
        "utf-8-sig": "utf-8",
        "utf-8": "utf-8"
    }
    return enc_map.get(enc.lower(), enc.lower())


def convert_to_ansi(root_dir: str, backup: bool = True):
    """
    批量转换 .c .h 文件为 ANSI(GBK)
    :param root_dir: 目标根目录
    :param backup: 是否备份原文件
    """
    backup_dir = os.path.join(root_dir, "ansi_backup")
    if backup and not os.path.exists(backup_dir):
        os.makedirs(backup_dir)

    count_total = 0
    count_convert = 0

    for dirpath, _, filenames in os.walk(root_dir):
        for fname in filenames:
            ext = os.path.splitext(fname)[1].lower()
            if ext not in (".c", ".h"):
                continue

            fpath = os.path.join(dirpath, fname)
            count_total += 1

            src_enc = get_file_encoding(fpath)
            if src_enc in ("gbk", "gb2312", "gb18030"):
                print(f"[跳过] {fpath} 已是ANSI编码")
                continue

            try:
                # 读取原文件
                with open(fpath, "r", encoding=src_enc, errors="replace") as f:
                    content = f.read()

                # 备份
                if backup:
                    rel_path = os.path.relpath(dirpath, root_dir)
                    dst_backup_sub = os.path.join(backup_dir, rel_path)
                    os.makedirs(dst_backup_sub, exist_ok=True)
                    shutil.copy2(fpath, os.path.join(dst_backup_sub, fname))

                # 写入GBK(ANSI)
                with open(fpath, "w", encoding="gbk", errors="replace") as f:
                    f.write(content)

                count_convert += 1
                print(f"[转换成功] {fpath}  {src_enc} -> ANSI(GBK)")

            except Exception as e:
                print(f"[失败] {fpath} 错误: {str(e)}")

    print(f"\n处理完毕：总计扫描 {count_total} 个[c/h]文件，成功转换 {count_convert} 个")
    if backup:
        print(f"原文件已备份至：{backup_dir}")


if __name__ == "__main__":
    # ====================== 在这里修改你的代码根目录 ======================
    target_folder = r"./"
    # ====================================================================

    # 开启备份更安全，第一次运行建议True
    convert_to_ansi(target_folder, backup=True)