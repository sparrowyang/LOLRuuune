export const applyRunePage = async (credentials, data) => {
  try {
    // 获取符文页信息
    const currentRuneList = (await createHttp1Request({
      method: "GET",
      url: 'lol-perks/v1/pages',
    }, credentials)).json()
    const current = currentRuneList.find((i) => i.current && i.isDeletable)
    if (current != undefined) {
      // 删除当前符文页
      await createHttp1Request({
        method: "DELETE",
        url: `lol-perks/v1/pages/${current.id}`,
      }, credentials)
    }
    // 写入新的符文页
    await createHttp1Request({
      method: "POST",
      url: 'lol-perks/v1/pages',
      body: data
    }, credentials)
    return true
  } catch (e) {
    console.log(e)
    return false
  }
}